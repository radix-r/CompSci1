// qick sort test area
//airports is data, first is 0, last is count-1 in main
void quicksort(airPdata* airports, int first, int last) {
  int pivot, j, i;
  int temp;

  if (first<last) {
    pivot = first;
    i = first;
    j = last;

    while (i<j) {
      while ((airports[i].latitude) <= (airports[pivot].latitude) && i < last)
        i++;
      while ((airports[j].latitude) > (airports[pivot].latitude))
        j--;
      if (i < j) {
        temp = airports[i].latitude;
        airports[i].latitude = airports[j].latitude;
        airports[j].latitude = temp;
      }
    }

    temp = airports[pivot].latitude;
    airports[pivot].latitude = airports[j].latitude;
    airports[j].latitude = temp;
    quicksort(airports, first, j - 1);
    quicksort(airports, j + 1, last);

  }
}
