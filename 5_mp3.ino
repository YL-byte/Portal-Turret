//Upload WAV Files to a TF Card and use it as the source for the sounds
void PlayWav(int8_t index) {
  delay(wavDelayTime);
  myMP3.playWithIndex(index + 1);
  delay(wavDelayTime);
}
