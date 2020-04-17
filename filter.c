#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            float avarage = (image[i][k].rgbtRed + image[i][k].rgbtBlue + image[i][k].rgbtGreen)/3;
            int data = (int) (avarage + 0.5);
            image[i][k].rgbtRed = data;
            image[i][k].rgbtBlue = data;
            image[i][k].rgbtGreen = data;
        }
    }
    return;
}
void swap(RGBTRIPLE* a, RGBTRIPLE* b)
{
    RGBTRIPLE tmp = *a;
    *a = *b;
    *b = tmp;
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int start = 0;
        int end = width;

        while (start < end){
            swap(&image[i][start], &image[i][end - 1]);
            start++;
            end--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE ogImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ogImage[i][j] = image[i][j];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int red, green, blue, counter;
            red = green = blue = 0;
            counter = 1;

            red += ogImage[h][w].rgbtRed;
            blue += ogImage[h][w].rgbtBlue;
            green += ogImage[h][w].rgbtGreen;


            if (h > 0 && w > 0){
                red += ogImage[h-1][w-1].rgbtRed;
                blue += ogImage[h-1][w-1].rgbtBlue;
                green += ogImage[h-1][w-1].rgbtGreen;
                counter++;
            }
            if (h > 0){
                red += ogImage[h-1][w].rgbtRed;
                blue += ogImage[h-1][w].rgbtBlue;
                green += ogImage[h-1][w].rgbtGreen;
                counter++;
            }
            if (h > 0 && w < (width-1)){
                red += ogImage[h-1][w+1].rgbtRed;
                blue += ogImage[h-1][w+1].rgbtBlue;
                green += ogImage[h-1][w+1].rgbtGreen;
                counter++;
            }

            if (w > 0){
                red += ogImage[h][w-1].rgbtRed;
                blue += ogImage[h][w-1].rgbtBlue;
                green += ogImage[h][w-1].rgbtGreen;
                counter++;
            }

            if (w < (width-1)){
                red += ogImage[h][w+1].rgbtRed;
                blue += ogImage[h][w+1].rgbtBlue;
                green += ogImage[h][w+1].rgbtGreen;
                counter++;
            }

            if (h < (height-1) && w > 0){
                red += ogImage[h+1][w-1].rgbtRed;
                blue += ogImage[h+1][w-1].rgbtBlue;
                green += ogImage[h+1][w-1].rgbtGreen;
                counter++;
            }
            if (h < (height-1)){
                red += ogImage[h+1][w].rgbtRed;
                blue += ogImage[h+1][w].rgbtBlue;
                green += ogImage[h+1][w].rgbtGreen;
                counter++;
            }
            if (h < (height-1) && w < (width-1)){
                red += ogImage[h+1][w+1].rgbtRed;
                blue += ogImage[h+1][w+1].rgbtBlue;
                green += ogImage[h+1][w+1].rgbtGreen;
                counter++;
            }

            image[h][w].rgbtRed = (int) (red/counter + 0.5);
            image[h][w].rgbtGreen = (int) (green/counter + 0.5);
            image[h][w].rgbtBlue = (int) (blue/counter + 0.5);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE ogImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ogImage[i][j] = image[i][j];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int gx_red, gx_blue, gx_green, gy_red, gy_blue, gy_green;
            gx_red = gx_blue = gx_green = gy_red = gy_blue = gy_green = 0;


            if (h > 0 && w > 0){
                gx_red -= ogImage[h-1][w-1].rgbtRed;
                gx_blue -= ogImage[h-1][w-1].rgbtBlue;
                gx_green -= ogImage[h-1][w-1].rgbtGreen;
                gy_red -= ogImage[h-1][w-1].rgbtRed;
                gy_blue -= ogImage[h-1][w-1].rgbtBlue;
                gy_green -= ogImage[h-1][w-1].rgbtGreen;
            }
            if (h > 0){
                gy_red -= 2*ogImage[h-1][w].rgbtRed;
                gy_blue -= 2*ogImage[h-1][w].rgbtBlue;
                gy_green -= 2*ogImage[h-1][w].rgbtGreen;
            }
            if (h > 0 && w < (width-1)){
                gx_red += ogImage[h-1][w+1].rgbtRed;
                gx_blue += ogImage[h-1][w+1].rgbtBlue;
                gx_green += ogImage[h-1][w+1].rgbtGreen;
                gy_red -= ogImage[h-1][w+1].rgbtRed;
                gy_blue -= ogImage[h-1][w+1].rgbtBlue;
                gy_green -= ogImage[h-1][w+1].rgbtGreen;
            }

            if (w > 0){
                gx_red -= 2*ogImage[h][w-1].rgbtRed;
                gx_blue -= 2*ogImage[h][w-1].rgbtBlue;
                gx_green -= 2*ogImage[h][w-1].rgbtGreen;
            }

            if (w < (width-1)){
                gx_red += 2*ogImage[h][w+1].rgbtRed;
                gx_blue += 2*ogImage[h][w+1].rgbtBlue;
                gx_green += 2*ogImage[h][w+1].rgbtGreen;
            }

            if (h < (height-1) && w > 0){
                gx_red -= ogImage[h+1][w-1].rgbtRed;
                gx_blue -= ogImage[h+1][w-1].rgbtBlue;
                gx_green -= ogImage[h+1][w-1].rgbtGreen;
                gy_red += ogImage[h+1][w-1].rgbtRed;
                gy_blue += ogImage[h+1][w-1].rgbtBlue;
                gy_green += ogImage[h+1][w-1].rgbtGreen;
            }
            if (h < (height-1)){
                gy_red += 2*ogImage[h+1][w].rgbtRed;
                gy_blue += 2*ogImage[h+1][w].rgbtBlue;
                gy_green += 2*ogImage[h+1][w].rgbtGreen;
            }
            if (h < (height-1) && w < (width-1)){
                gx_red += ogImage[h+1][w+1].rgbtRed;
                gx_blue += ogImage[h+1][w+1].rgbtBlue;
                gx_green += ogImage[h+1][w+1].rgbtGreen;
                gy_red += ogImage[h+1][w+1].rgbtRed;
                gy_blue += ogImage[h+1][w+1].rgbtBlue;
                gy_green += ogImage[h+1][w+1].rgbtGreen;
            }

            float final_red = sqrt((gx_red * gx_red) + (gy_red * gy_red));
            float final_blue = sqrt((gx_blue * gx_blue) + (gy_blue * gy_blue));
            float final_green = sqrt((gx_green * gx_green) + (gy_green * gy_green));

            if (final_red > 255)
            {
                final_red = 255;
            }
            if (final_blue > 255)
            {
                final_blue = 255;
            }
            if (final_green > 255)
            {
                final_green = 255;
            }
            if (final_red < 0)
            {
                final_red = 0;
            }
            if (final_blue < 0)
            {
                final_blue = 0;
            }
            if (final_green < 0)
            {
                final_green = 0;
            }

            image[h][w].rgbtRed = (int) (final_red + 0.5);
            image[h][w].rgbtBlue = (int) (final_blue + 0.5);
            image[h][w].rgbtGreen = (int) (final_green + 0.5);
        }
    }
    return;
}
