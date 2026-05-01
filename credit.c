#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //gets input from user
    long input = get_long("Number: ");

    string cType;

    long fDigit = 0;
    int digits = 0;

    //auto invalid
    if (input > 5599999999999999 || input < 3400000000000)
    {
        cType = "INVALID";
    }

    //13 digits-only VISA
    if (input <= 4999999999999 && input >= 4000000000000)
    {
        long ques = input % 1000000000000;
        long step = input - ques;
        fDigit = step / 1000000000000;
        digits = 13;
        printf("VISA identified");
    }
    //14 digits - none
    else if (input <= 99999999999999 && input >= 10000000000000)
    {
      cType = "INVALID";
    }
    //15 digits - AMEX
    else if (input <= 379999999999999 && input >= 340000000000000)
    {
        long ques = input % 10000000000000;
        long step = input - ques;
        fDigit = step / 10000000000000;
        digits = 15;
    }
    //16 digits - VISA
    else if (input <= 4999999999999999 && input >= 4000000000000000)
    {
        long ques = input % 1000000000000000;
        long calc = input - ques;
        fDigit = calc / 1000000000000000;
        digits = 16;
    }
    //16 digits - MASTERCARD
    else if (input <= 5599999999999999 && input >= 5100000000000000)
    {
        long ques = input % 100000000000000;
        long calc = input - ques;
        fDigit = calc / 100000000000000;
        digits = 16;
    }
    //other values in range but not listed type
    else
    {
        cType = "INVALID";
    }

    //identifies potential type of card
    if ((digits == 13 || digits == 16) && fDigit == 4)
    {
        cType = "VISA";
    }
    else if ((fDigit == 34 || fDigit == 37) && digits == 15)
    {
        cType = "AMEX";
    }
    else if ((fDigit == 51 || fDigit == 52 || fDigit == 53 || fDigit == 54 || fDigit == 55) && digits == 16)
    {
        cType = "MASTERCARD";
    }
    else
    {
        cType = "INVALID";
    }

    int number[16];
    int numbers = 0;
    int q = 0;

    //gets every other digit starting from second digit, multiples by 2 then stores them in "number" string
    for (long mul = 100, i = 1, z = 0; i < (digits/2)+1; i++, mul = mul * 100, z++)
    {
        long ans = input % mul;
        long n;
        n = ans % (mul/10);
        ans = ans - n;
        long num = (ans / (mul/10))*2;
        if (num > 9)
        {
           int num1 = num % 10;
           number[z+q] = num1;
           int num2 = (num - num1)/10;
           number[z+q+1] = num2;
           q = q + 1;
        }
        else
        {
            number[z+q] = num;
        }
        numbers = numbers + 1;
    }
    
    int nums = number[0] + number[1] + number[2] + number[3] + number[4] + number[5] + number[6] + number[7];
    int product = nums + number[8] + number[9] + number[10] + number[11] + number[12] + number[13] + number[14] + number[15];
    
    int sum = 0;
    
    //configures amount of times the following for loop runs
    if (digits == 15)
    {
        digits = 8;
    }
    else if (digits == 13)
    {
        digits = 7;
    }
    else
    {
        digits = digits/2;
    }
    
    //gets the numbers which weren't multiplied by 2 and adds them to the product
    for (long mul = 10, i = 1; i < digits+1; i++, mul = mul * 100)
    {
        long ans = input % mul;
        long n;
        n = ans % (mul/10);
        ans = ans - n;
        long num = ans / (mul/10);
        if (i == 1)
        {
            sum = num + product;
        }
        else
        {
            sum += num;
        }
    }
    
    //if the total's last digit is 0, then it prints type, else it prints INVALID
    int total = sum % 10;
    if (total == 0)
    {
        printf("%s\n", cType);
    }
    else 
    {
        printf("INVALID\n");
    }
}
