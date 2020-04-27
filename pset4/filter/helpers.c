#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include <math.h> //needed for square root
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double average = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = ((double)image[i][j].rgbtRed + (double)image[i][j].rgbtGreen + (double)image[i][j].rgbtBlue) / 3.0;
            if ((int)(average + .5) > (int)(average))
            {
                average = (int)(average + .5);
            }
            else
            {
                average = (int)(average);
            }

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;

        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tempRed;
    int tempGreen;
    int tempBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tempRed = image[i][j].rgbtRed;
            tempGreen =  image[i][j].rgbtGreen;
            tempBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed =  image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = tempRed;
            image[i][width - j - 1].rgbtGreen = tempGreen;
            image[i][width - j - 1].rgbtBlue = tempBlue;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE Image[height][width])
{
    double avgRed = 0;
    double avgGreen = 0;
    double avgBlue = 0;
    double counter = 0;

    RGBTRIPLE image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = Image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int h = -1; h <= 1; h++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (i + h >= 0 && i + h < height && j + l >= 0 && j + l < width)
                    {
                        avgRed += (double)image[i + h][j + l].rgbtRed;
                        avgGreen += (double)image[i + h][j + l].rgbtGreen;
                        avgBlue += (double)image[i + h][j + l].rgbtBlue;
                        counter++;
                    }
                }
            }

            avgRed = avgRed / counter;
            avgGreen = avgGreen / counter;
            avgBlue = avgBlue / counter;

            if ((int)(avgRed + .5) > (int)(avgRed))
            {
                avgRed = (int)(avgRed + .5);
            }
            else
            {
                avgRed = (int)(avgRed);
            }

            if ((int)(avgGreen + .5) > (int)(avgGreen))
            {
                avgGreen = (int)(avgGreen + .5);
            }
            else
            {
                avgGreen = (int)(avgGreen);
            }

            if ((int)(avgBlue + .5) > (int)(avgBlue))
            {
                avgBlue = (int)(avgBlue + .5);
            }
            else
            {
                avgBlue = (int)(avgBlue);
            }

            Image[i][j].rgbtRed = avgRed;
            Image[i][j].rgbtGreen = avgGreen;
            Image[i][j].rgbtBlue = avgBlue;

            avgRed = 0;
            avgGreen = 0;
            avgBlue = 0;
            counter = 0;

        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE Image[height][width])
{
    double Gx_redVal = 0;
    double Gy_redVal = 0;
    double Gx_blueVal = 0;
    double Gy_blueVal = 0;
    double Gx_greenVal = 0;
    double Gy_greenVal = 0;
    double redTotal = 0;
    double greenTotal = 0;
    double blueTotal = 0;
    int xweights[3][3] = {{-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int yweights[3][3] = {{-1, -2, -1},
        {-0, 0, 0},
        {1, 2, 1}
    };

    RGBTRIPLE image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = Image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int h = -1; h <= 1; h++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (i + h >= 0 && i + h < height && j + l >= 0 && j + l < width)
                    {
                        Gx_redVal += xweights[h + 1][l + 1] * image[i + h][j + l].rgbtRed;
                        Gx_greenVal += xweights[h + 1][l + 1] * image[i + h][j + l].rgbtGreen;
                        Gx_blueVal +=  xweights[h + 1][l + 1] * image[i + h][j + l].rgbtBlue;

                        Gy_redVal += yweights[h + 1][l + 1] * image[i + h][j + l].rgbtRed;
                        Gy_greenVal += yweights[h + 1][l + 1] * image[i + h][j + l].rgbtGreen;
                        Gy_blueVal += yweights[h + 1][l + 1] * image[i + h][j + l].rgbtBlue;
                    }
                }
            }

            redTotal = sqrt(((Gx_redVal * Gx_redVal) + (Gy_redVal * Gy_redVal)));
            greenTotal = sqrt(((Gx_greenVal * Gx_greenVal) + (Gy_greenVal * Gy_greenVal)));
            blueTotal = sqrt(((Gx_blueVal * Gx_blueVal) + (Gy_blueVal * Gy_blueVal)));

            if (redTotal > 255)
            {
                redTotal = 255;
            }
            if (greenTotal > 255)
            {
                greenTotal = 255;
            }
            if (blueTotal > 255)
            {
                blueTotal = 255;
            }

            if ((int)(redTotal + .5) > (int)(redTotal))
            {
                redTotal = (int)(redTotal + .5);
            }
            else
            {
                redTotal = (int)(redTotal);
            }

            if ((int)(greenTotal + .5) > (int)(greenTotal))
            {
                greenTotal = (int)(greenTotal + .5);
            }
            else
            {
                greenTotal = (int)(greenTotal);
            }

            if ((int)(blueTotal + .5) > (int)(blueTotal))
            {
                blueTotal = (int)(blueTotal + .5);
            }
            else
            {
                blueTotal = (int)(blueTotal);
            }

            Image[i][j].rgbtRed = (int)redTotal;
            Image[i][j].rgbtGreen = (int)greenTotal;
            Image[i][j].rgbtBlue = (int)blueTotal;

            Gx_redVal = 0;
            Gy_redVal = 0;
            Gx_blueVal = 0;
            Gy_blueVal = 0;
            Gx_greenVal = 0;
            Gy_greenVal = 0;
            redTotal = 0;
            greenTotal = 0;
            blueTotal = 0;
        }
    }
}
