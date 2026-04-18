#include <stdio.h>
//pattern inc alternate number 1 2 4 5 7 8 ....
#define INC_NUM 3
#define NUM_TO_ENTER 12 //could be dynamic i've fixed to 12
int main()
{

  int print_val_even=1;
  int print_val_odd =2;
  for(int itr_var= 0; itr_var < NUM_TO_ENTER;itr_var++)
  {
      if(itr_var%2== 0)
      {
          printf("%d\t",print_val_even);
          print_val_even += INC_NUM;
      }
      else
      {
          printf("%d\t",print_val_odd);
          print_val_odd += INC_NUM;
      }
  }

}
