# ifndef SPK_CORE_H
# define SPK_CORE_H

# include <stdio.h>
# include <string.h>
# include <assert.h>

# include <sys/select.h>

# include <sphinxbase/err.h>
# include <sphinxbase/ad.h>

# include "pocketsphinx.h"

void recognize_from_microphone();
int speak_init();
int speak_exit();

# endif // SPK_CORE_H
