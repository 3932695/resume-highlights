--------------------------------------------------------------------------------

< DOSTUNES >

A musical recording and playback program written in x86 assembly language.

--------------------------------------------------------------------------------

Needs DOSBOX (an x86 emulator) to run. Download from "http://www.dosbox.com".

Steps:

1. Run DOSBOX.

2. Type "mount c c:\MSDOS" ...or wherever the MSDOS folder is stored. 

3. Type "c:" to navigate to DOSBOX's virtual c drive.

4. Type "cd dostune" to navigate to the dostune folder.

5. Type "dostune" to run the program.

6. Follow program instructions for recording and playback.

The folder has a few files readily available for playback demonstration. They 
are named with the letter Z plus a relevant word (e.g. "ZBee" will play Flight 
of the Bumblebee, and "ZList" will play the main theme to Schindler's List). 

Recording a melody is similar to playing a flute. Tapping the shift key will 
write notes to a recording file, as if you were blowing the flute. 

The following keys on the keyboard will adjust pitch:
 S D   G H   K L ;   2 3   5 6 7   9 0   =
Z X C V B N M , . / Q W E R T Y U I O P [ ]
- The arrangement is not arbitrary; it is based on the keys of a piano...
- ...so from left to right; lowest to highest pitch...
- ...'black keys' on the first row, and 'white keys' on the second row.
- Pressing any key outside of these keys will record a rest/silent note.

For the sake of convenience, recording doesn't quite happen in 'real time'.
Rather, the recording happens in an almost turn-based fashion:

- As long as the user is not pressing the shift key, nothing will be recorded. 
- Tapping the shift key once records a note of the smallest possible length.
- To record a longer note, tap shift more than once without changing the pitch. 



