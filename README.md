### SpeakCode v1.0

#### Introduction

- Github: https://github.com/LyricZhao/SpeakCode

- A code editor with ***Speech Recognition***.

- Developed by LyricZ.

- An OOP Project, 2018 Spring.

- Just by simply speaking the code, you do not have to use your hand!

  

#### Environments

- Local Compiling Environment
  - macOS 10.13.4
  - QT 5.10.1
  - Clang 902.0.39.1
- Dependences
  - Qt 5.10.1
  - SphinxBase
  - Pocketsphinx
- I also compiled and packaged an app which can directly run on macOS.

#### How to use

- The **Open/Save** Button is for file management.
- Press the **Speak** Button, you can say something (only a few words can be recognized, later it will be told)
- You can change the special words you want to speak using the **Settings** menu.
  - For example, you want to input "iostream" in your code, you must first change the settings by setting the String 1 to "iostream".
  - Later, you can input "iostream" by speaking "string one".
- The words can be recognized (Sorry for its low recognition rate, I spent a lot of time to tune, but ...):
  - Words:
    - a to z
    - one to ten
    - auto
    - break
    - case
    - catch
    - class
    - const
    - continue
    - define
    - delete
    - do
    - else
    - endif
    - extern
    - false
    - friend
    - for
    - if
    - ifdef
    - include
    - inline
    - new
    - operator
    - pravite
    - public
    - return
    - sizeof
    - static
    - struct
    - switch
    - template
    - this
    - throw
    - true
    - typedef
    - while
    - bool
    - double
    - float
    - int
    - long
    - short
    - size_t
    - unsigned
    - void
  - Keys:
    - backspace
    - space
    - tab
    - up
    - down
    - left
    - right
  - Specal (You can define what it means):
    - function
    - string
    - variable
  - Signs:
    - and &
    - apostrophe '
    - at @
    - backslash \
    - colon :
    - comma ,
    - cut -
    - divide /
    - dollar $
    - dot .
    - equal =
    - exclusive or ^
    - hashtag #
    - left big bracket {
    - left bracket (
    - left square bracket [
    - less <
    - mark !
    - model %
    - more >
    - multiply *
    - negate ~
    - or |
    - plus +
    - question ?
    - right big bracket }
    - right bracket )
    - right square bracket ]
    - semicolon ;
    - underline _

#### Workload

- About **1.5k** LoC.
- The most difficult part is linking the CMUSphinux to my QT program.
- And I have no experience on QT, I spent a little time to learn it, it also needs my effort.
- What's more, I also spent time on compiling and packing my program into an App which can run on all the macOS devices.

#### Enjoy it!
