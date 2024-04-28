#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void play_normal(char *input) {
  char command[59];
  sprintf(command, "mpv common/%s.mp4 --loop-file=inf --msg-level=all=no --fs",
          input);
  system(command);
}

void create_playlist(const char *vidIndex) {
  FILE *m3uFile = fopen("common/playlist.m3u", "w");
  if (m3uFile != NULL) {
    int index = atoi(vidIndex);
    for (int i = 1; i <= index; i++) {
      fprintf(m3uFile, "%d.mp4\n", i);
    }
    fclose(m3uFile);
    system("mpv --playlist=common/playlist.m3u --loop-playlist=inf --msg-level=all=no --fs");
  } else {
    printf("ERR_M3U_NULL\n");
  }
}

void run_command(const char *input) {
  switch (input[0]) {
  case '0':
    system("clear\n");
    break;
  case '1':
    system("cat catalog.txt\n");
    break;
  case '2':
    system("cat ~/.config/mpv/input.conf\n");
    break;
  case '3':
    system("sudo reboot");
    break;
  default:
    printf("ERR_ILLEGAL_COMMAND\n");
    break;
  }
}

void open_pdf(const char *input) {
  char command[31];
  sprintf(command, "mupdf -z 100 -f common/%s.pdf", input);
  system(command);
}

void filter(char *input) {
  if (isdigit(input[0])) {
    play_normal(input);
  } else {
    switch (input[0]) {
    case '*':
      create_playlist(input + 1);
      break;
    case '+':
      run_command(input + 1);
      break;
    case '-':
      open_pdf(input + 1);
      break;
    default:
      printf("ERR_ILLEGAL_INPUT\n");
      break;
    }
  }
}

int main() {
  char input[5];
  system("printf \"%s\" \"$(cat splash.txt)\"");
  while (1) {
    printf("> ");
    scanf("%4s", input);
    filter(input);
  }
  return 0;
}