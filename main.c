#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void play_normal(char *input, char *args) {
  char command[100];
  sprintf(command, "mpv common/%s.mp4 --loop --msg-level=all=no --fs %s", input, args);
  system(command);
}

void create_playlist(const char *vidIndex, char *args) {
  FILE *m3uFile = fopen("common/playlist.m3u", "w");
  if (m3uFile != NULL) {
    int index = atoi(vidIndex);
    for (int i = 1; i <= index; i++) {
      fprintf(m3uFile, "%d.mp4\n", i);
    }
    if (fclose(m3uFile) != 0) {
      printf("ERR_M3U_SAVE");
    } else {
      char command[100];
      sprintf(command, "mpv common/playlist.m3u --loop-playlist --msg-level=all=no --fs %s", args);
      system(command);
    }
  } else {
    printf("ERR_M3U_NULL\n");
  }
}

void run_command(const char *input, char *args) {
  switch (input[0]) {
  case '0':
    system("clear");
    break;
  case '1':
    system("cat catalog.txt");
    printf("\n");
    break;
  case '2':
    system("cat ~/.config/mpv/input.conf");
    printf("\n");
    break;
  case '3':
    system("sudo reboot"); // adjust based on init system
    break;
  case '4':
    create_playlist("99", "--shuffle");
    break;
  default:
    printf("ERR_ILLEGAL_COMMAND\n");
    break;
  }
}

void open_pdf(const char *input) {
  char command[50];
  sprintf(command, "mupdf -z 100 -f common/%s.pdf", input);
  system(command);
}

void filter(char *input) {
  char args[1] = "\0"; // args still must be passed; set args to null initially
  if (isdigit(input[0])) {
    play_normal(input, args);
  } else {
    switch (input[0]) {
    case '*':
      create_playlist(input + 1, args);
      break;
    case '+':
      run_command(input + 1, args);
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
  system("echo \"$(cat splash.txt)\""); // add -e argument for escape codes on ksh/openbsd
  while (1) {
    printf("> ");
    scanf("%4s", input);
    filter(input);
  }
  return 0;
}
