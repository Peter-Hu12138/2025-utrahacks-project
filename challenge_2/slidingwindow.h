void addnew(int* array, int newval, int histlength){
  for (int i = 0; i < histlength - 1; i++) {
    array[i] = array[i + 1];
  }
  array[histlength - 1] = newval;
}

int colouraverage(int* colours, int histlength){
  int red_sum = 0;
  int green_sum = 0;
  int blue_sum = 0;
  int black_sum = 0;
  for (int i = 0; i < histlength; i++) {
    switch(colours[i]){
      case 0:
        red_sum++;
        break;
      case 1:
        blue_sum++;
        break;
      case 2:
        green_sum++;
        break;
      case -1:
        black_sum++;
        break;
    };
  };
  int maxcol = max(red_sum, max(blue_sum, max(green_sum, black_sum)));
  if (maxcol == red_sum) {
      return 0;
  }
  if (maxcol == blue_sum) {
    return 1;
  }
  if (maxcol == green_sum) {
    return 2;
  }
  return -1;
};