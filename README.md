# kiosk

add videos `[indexed].mp4` in common/

add pdfs `[indexed].pdf` in common/

add catalog of videos/pdfs in `catalog.txt`

add splash text in `splash.txt`, compatible with `printf`/`echo -e` formatting

install mpv & mupdf

designed to work on bash and ksh


## by default:

| format  | action                                 |
|---------|----------------------------------------|
| 0       | Play video                             |
| *0      | Play playlist from index 1 to indicated index & loop |
| +0      | Execute command                        |
| -0      | Open PDF                               |


## commands:

| command | action                                    |
|---------|-------------------------------------------|
| +0      | Clear screen                              |
| +1      | Read the catalog/info                     |
| +2      | Show mpv keybinds                         |
| +3      | Reboot (password required)                |
| +4      | Play all videos in a random order infinitely |
