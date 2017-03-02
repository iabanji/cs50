#include <cs50.h>
 
#include "helpers.h"

bool search(int value, int values[], int n)
{
 if (n < 1)
 {
  return false;
 }
 else
 {
  for (int i = 0; i < n+1; i++)
  {
   if (values[i] == value)
    return true;
  }
 }
 return false;
}
 
void sort(int values[], int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
     if (values[j+1] < values[j])
     {
      int tmp = values[j];
      values[j] = values[j+1];
      values[j+1] = tmp;
            }
    }
   }
 }
 