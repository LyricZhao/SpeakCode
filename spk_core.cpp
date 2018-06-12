# include <cstdlib>
# include <iostream>
# include <mach-o/dyld.h>

# include "writer.h"
# include "spk_core.h"
# include "mainwindow.h"

# define OUTPUT_INFO

extern MainWindow *mwin;
extern Writer resultWriter;

static const arg_t cont_args_def[] = {
    POCKETSPHINX_OPTIONS,
    /* Argument file. */
    {"-argfile",
     ARG_STRING,
     NULL,
     "Argument file giving extra arguments."},
    {"-adcdev",
     ARG_STRING,
     NULL,
     "Name of audio device to use for input."},
    {"-infile",
     ARG_STRING,
     NULL,
     "Audio file to transcribe."},
    {"-inmic",
     ARG_BOOLEAN,
     "no",
     "Transcribe audio from microphone."},
    {"-time",
     ARG_BOOLEAN,
     "no",
     "Print word times in file transcription."},
    CMDLN_EMPTY_OPTION
};

static ps_decoder_t *ps;
static cmd_ln_t *config;
// static FILE *rawfd;

/*
static void
print_word_times()
{
    int frame_rate = cmd_ln_int32_r(config, "-frate");
    ps_seg_t *iter = ps_seg_iter(ps);
    while (iter != NULL) {
        int32 sf, ef, pprob;
        float conf;

        ps_seg_frames(iter, &sf, &ef);
        pprob = ps_seg_prob(iter, NULL, NULL, NULL);
        conf = logmath_exp(ps_get_logmath(ps), pprob);
        printf("%s %.3f %.3f %f\n", ps_seg_word(iter), ((float)sf / frame_rate),
               ((float) ef / frame_rate), conf);
        iter = ps_seg_next(iter);
    }
}
*/

/*
static int
check_wav_header(char *header, int expected_sr)
{
    int sr;

    if (header[34] != 0x10) {
        E_ERROR("Input audio file has [%d] bits per sample instead of 16\n", header[34]);
        return 0;
    }
    if (header[20] != 0x1) {
        E_ERROR("Input audio file has compression [%d] and not required PCM\n", header[20]);
        return 0;
    }
    if (header[22] != 0x1) {
        E_ERROR("Input audio file has [%d] channels, expected single channel mono\n", header[22]);
        return 0;
    }
    sr = ((header[24] & 0xFF) | ((header[25] & 0xFF) << 8) | ((header[26] & 0xFF) << 16) | ((header[27] & 0xFF) << 24));
    if (sr != expected_sr) {
        E_ERROR("Input audio file has sample rate [%d], but decoder expects [%d]\n", sr, expected_sr);
        return 0;
    }
    return 1;
}
*/

/* Sleep for specified msec */
static void
sleep_msec(int32 ms)
{
#if (defined(_WIN32) && !defined(GNUWINCE)) || defined(_WIN32_WCE)
    Sleep(ms);
#else
    /* ------------------- Unix ------------------ */
    struct timeval tmo;

    tmo.tv_sec = 0;
    tmo.tv_usec = ms * 1000;

    select(0, NULL, NULL, NULL, &tmo);
#endif
}

/*
 * Main utterance processing loop:
 *     for (;;) {
 *        start utterance and wait for speech to process
 *        decoding till end-of-utterance silence will be detected
 *        print utterance result;
 *     }
 */
void
recognize_from_microphone()
{
    ad_rec_t *ad;
    int16 adbuf[2048];
    uint8 utt_started, in_speech;
    int32 k;
    char const *hyp;

    if ((ad = ad_open_dev(cmd_ln_str_r(config, "-adcdev"),
                          (int) cmd_ln_float32_r(config,
                                                 "-samprate"))) == NULL)
        E_FATAL("Failed to open audio device\n");
    if (ad_start_rec(ad) < 0)
        E_FATAL("Failed to start recording\n");

    if (ps_start_utt(ps) < 0)
        E_FATAL("Failed to start utterance\n");
    utt_started = FALSE;
# ifdef OUTPUT_INFO
    E_INFO("Ready....\n");
# endif

    for (;;) {
        if ((k = ad_read(ad, adbuf, 2048)) < 0)
            E_FATAL("Failed to read audio\n");
        ps_process_raw(ps, adbuf, k, FALSE, FALSE);
        in_speech = ps_get_in_speech(ps);
        if (in_speech && !utt_started) {
            utt_started = TRUE;
# ifdef OUTPUT_INFO
            E_INFO("Listening ....\n");
            mwin -> printOnConsoleWON(std:: string("Listening ....\n"));
# endif
        }
        if (!in_speech && utt_started) {
            /* speech -> silence transition, time to start new utterance  */
            ps_end_utt(ps);
            hyp = ps_get_hyp(ps, NULL );
            if (hyp != NULL) {
                printf("%s\n", hyp);
                mwin -> printOnConsoleWON(std:: string("Result: ") + std:: string(hyp) + std:: string("\n"));
                resultWriter.commandIntoAction(std:: string(hyp));
                fflush(stdout);
            }
            break;

            if (ps_start_utt(ps) < 0)
                E_FATAL("Failed to start utterance\n");
            utt_started = FALSE;
            E_INFO("Ready....\n");
        }
        sleep_msec(100);
    }
    ad_close(ad);
}

int speak_init() {
    // std:: cout << "here" << std:: endl;
    // first we need to find the path
    char g_path[1024];
    unsigned int psz = 1024;
    _NSGetExecutablePath(g_path, &psz);
    // std:: cout << g_path << std:: endl;
    psz = strlen(g_path) - 10;

    mwin -> printOnConsoleWON(std:: string("Loading speaking config .... "));
    int argc = 9;

    char **argv = (char **) malloc(9 * sizeof(char *));

    // argv[0]
    argv[0] = (char *) malloc(sizeof(char) * 1024);
    memcpy(argv[0], g_path, psz);
    char *ta0 = (char *) "/pocketsphinx_continuous";
    memcpy(argv[0] + psz, ta0, strlen(ta0) + 1);
    // std:: cout << argv[0] << std:: endl;

    // argv[1]
    argv[1] = (char *) "-hmm";

    // argv[2]
    argv[2] = (char *) malloc(sizeof(char) * 1024);
    memcpy(argv[2], g_path, psz);
    char *ta2 = (char *) "/en-us-semi/";
    memcpy(argv[2] + psz, ta2, strlen(ta2) + 1);
    // std:: cout << argv[2] << std:: endl;

    // argv[3]
    argv[3] = (char *) "-dict";

    // argv[4]
    argv[4] = (char *) malloc(sizeof(char) * 1024);
    memcpy(argv[4], g_path, psz + 1);
    char *ta4 = (char *) "/TAR0572/0572.dic";
    memcpy(argv[4] + psz, ta4, strlen(ta4) + 1);
    // std:: cout << argv[4] << std:: endl;

    // argv[5]
    argv[5] = (char *) "-lm";

    // argv[6]
    argv[6] = (char *) malloc(sizeof(char) * 1024);
    memcpy(argv[6], g_path, psz);
    char *ta6 = (char *) "/TAR0572/0572.lm";
    memcpy(argv[6] + psz, ta6, strlen(ta6) + 1);
    // std:: cout << argv[6] << std:: endl;

    // argv[7]
    argv[7] = (char *) "-inmic";

    // argv[8]
    argv[8] = (char *) "yes";

    char const *cfg;
    config = cmd_ln_parse_r(NULL, cont_args_def, argc, argv, TRUE);

    /* Handle argument file as -argfile. */
    if (config && (cfg = cmd_ln_str_r(config, "-argfile")) != NULL) {
        config = cmd_ln_parse_file_r(config, cont_args_def, cfg, FALSE);
    }

    if (config == NULL || (cmd_ln_str_r(config, "-infile") == NULL && cmd_ln_boolean_r(config, "-inmic") == FALSE)) {
# ifdef OUTPUT_INFO
        E_INFO("Specify '-infile <file.wav>' to recognize from file or '-inmic yes' to recognize from microphone.\n");
# endif
        cmd_ln_free_r(config);
        assert(0); // error
        return -1;
    }

    ps_default_search_args(config);
    ps = ps_init(config);
    if (ps == NULL) {
        cmd_ln_free_r(config);
        return 1;
    }

# ifdef OUTPUT_INFO
    E_INFO("%s COMPILED ON: %s, AT: %s\n\n", argv[0], __DATE__, __TIME__);
# endif

    // recognize_from_microphone();

    free(argv[0]);
    free(argv[2]);
    free(argv[4]);
    free(argv[6]);

    free(argv);

    mwin -> printOnConsoleWON(std:: string("ok !\n"));
    return 1;
}

int speak_exit() {
    ps_free(ps);
    cmd_ln_free_r(config);
    return 1;
}

