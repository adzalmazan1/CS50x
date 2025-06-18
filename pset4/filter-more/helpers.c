#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.00);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid = round(width / 2.00);
    // temp
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < mid; j++)
        {
            image[i][j].rgbtRed = temp[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = temp[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = temp[i][j].rgbtRed;
            image[i][width - j - 1].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][width - j - 1].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    // performing box blur
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double aveRed = 0, aveGrn = 0, aveBlu = 0, pixelCnt = 0;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if ((i + k >= 0 && i + k < height) && (j + l >= 0 && j + l < width))
                    {
                        aveRed += temp[i + k][j + l].rgbtRed;
                        aveGrn += temp[i + k][j + l].rgbtGreen;
                        aveBlu += temp[i + k][j + l].rgbtBlue;
                        pixelCnt++;
                    }
                }
            }

            image[i][j].rgbtRed = round(aveRed / pixelCnt);
            image[i][j].rgbtGreen = round(aveGrn / pixelCnt);
            image[i][j].rgbtBlue = round(aveBlu / pixelCnt);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    int gx[][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double gxRed = 0, gxGrn = 0, gxBlu = 0;
            double gyRed = 0, gyGrn = 0, gyBlu = 0;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // if within bounds
                    if ((i + k >= 0 && i + k < height) && (j + l >= 0 && j + l < width))
                    {
                        gxRed += temp[i + k][j + l].rgbtRed * gx[k + 1][l + 1];
                        gxGrn += temp[i + k][j + l].rgbtGreen * gx[k + 1][l + 1];
                        gxBlu += temp[i + k][j + l].rgbtBlue * gx[k + 1][l + 1];

                        gyRed += temp[i + k][j + l].rgbtRed * gy[k + 1][l + 1];
                        gyGrn += temp[i + k][j + l].rgbtGreen * gy[k + 1][l + 1];
                        gyBlu += temp[i + k][j + l].rgbtBlue * gy[k + 1][l + 1];
                    }
                    else
                    {
                        continue;
                    }
                }
            }

            int capValue = 255;

            int newRed = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));
            int newGrn = round(sqrt(pow(gxGrn, 2) + pow(gyGrn, 2)));
            int newBlu = round(sqrt(pow(gxBlu, 2) + pow(gyBlu, 2)));

            if (newRed > 255)
            {
                newRed = capValue;
            }
            if (newGrn > 255)
            {
                newGrn = capValue;
            }
            if (newBlu > 255)
            {
                newBlu = capValue;
            }

            image[i][j].rgbtRed = newRed;
            image[i][j].rgbtGreen = newGrn;
            image[i][j].rgbtBlue = newBlu;
        }
    }

    return;
}
