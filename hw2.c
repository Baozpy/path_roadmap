/*
Name: Baozan Yan 
Date: 06/06/2022 
Description: Dynamic Allocation of multi-dimension arrays
Usage: Enter the values as prompted and generate wave.txt file to form the road map
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

int **map = NULL;
char **wave_map = NULL;
int map_width, map_height;
int percent;
int goal_x = 0, goal_y = 0, start_x = 0, start_y = 0;

void free_wave_map()
{
    for (int i = 0; i < map_height; i++)
    {
        free(wave_map[i]);
    }
    free(wave_map);
    wave_map = NULL;
}

void free_map()
{
    for (int i = 0; i < map_height; i++)
    {
        free(map[i]);
    }
    free(map);
    map = NULL;
}

void init_map(int percent)
{
    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            map[i][j] = 0;
        }
    }

    int total = map_height * map_width;
    double per = (double)percent / 100.0;
    int impassible = (double)total * per;
    int x, y;
    struct timeval time;

    while (impassible)
    {
        gettimeofday(&time, NULL);
        srand(time.tv_usec);
        x = rand() % map_height;
        y = rand() % map_width;
        if (map[x][y] == 0)
        {
            impassible--;
            map[x][y] = -1;
        }
    };
}

int input_init()
{
    printf("Please tell me about the grid you want to generate.\n");
    do
    {
        printf("Enter the width (at least 10):");
        scanf("%d", &map_width);
    } while (map_width < 10);

    do
    {
        printf("Enter the height (at least 10):");
        scanf("%d", &map_height);
    } while (map_height < 10);

    map = (int **)malloc(sizeof(int *) * map_height);
    if (NULL == map)
    {
        return -1;
    }
    for (int i = 0; i < map_height; i++)
    {
        map[i] = malloc(sizeof(int) * map_width);
        if (NULL == map[i])
        {
            free_map();
            return -1;
        }
    }

    do
    {
        printf("Enter the percent of impassible terrain (0 - 100):");
        scanf("%d", &percent);
        if (percent > 35)
        {
            char ch;
            ch = getchar();
            printf("Having a value greater than 35% might create poor results, do you wish to continue? (y/n):");
            ch = getchar();
            if (ch != 'y')
            {
                continue;
            }
        }

    } while (percent < 0 || percent > 100);

    init_map(percent);
}

int file_init(char *path)
{
    FILE *fp = fopen(path, "r");
    if (NULL == fp)
    {
        return -1;
    }

    char buff[1024] = {0};
    fgets(buff, sizeof(buff), fp);
    map_height = atoi(buff);

    memset(buff, 0, sizeof(buff));
    fgets(buff, sizeof(buff), fp);
    map_width = atoi(buff);

    map = (int **)malloc(sizeof(int *) * map_height);
    if (NULL == map)
    {
        fclose(fp);
        return -1;
    }
    for (int i = 0; i < map_height; i++)
    {
        map[i] = malloc(sizeof(int) * map_width);
        if (NULL == map[i])
        {
            free_map();
            fclose(fp);
            return -1;
        }
    }
    int row = 0, column = 0;
    while (fgets(buff, sizeof(buff), fp))
    {
        int len = strlen(buff);
        for (int i = 0; i < len; i++)
        {
            if (buff[i] != ' ')
            {
                if (buff[i] == '0')
                {
                    map[row][column] = 0;
                }
                else
                {
                    map[row][column] = -1;
                }
            }
        }
        row++;
    }
}

void PrintEnvironment(int **array, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%2d ", array[i][j]);
        }
        printf("\n");
    }
}

void PrintEnvironmentc(char **array, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%c", array[i][j]);
        }
        printf("\n");
    }
}

void get_goal_site()
{
    do
    {
        printf("Please enter the Goal Position X:");
        scanf("%d", &goal_x);
    } while (goal_x > map_width || goal_x < 0);

    do
    {
        printf("Please enter the Goal Position Y:");
        scanf("%d", &goal_y);
    } while (goal_y > map_height || goal_y < 0);
}

void get_start_site()
{
    do
    {
        printf("Please enter the Start Position X:");
        scanf("%d", &start_x);
    } while (start_x > map_width || start_x < 0);

    do
    {
        printf("Please enter the Start Position Y:");
        scanf("%d", &start_y);
    } while (start_y > map_width || start_y < 0);
}

void running_wave_one(int start_x, int start_y)
{
    int x, y;

    y = start_y;
    x = start_x;
    while (x > 0)
    {
        if (map[x - 1][y] == -1 || map[x - 1][y] > 0)
        {
            break;
        }
        map[x - 1][y] = map[x][y] + 1;
        x--;
    }
    x = start_x;
    while (x < map_width - 1)
    {
        if (map[x + 1][y] == -1 || map[x + 1][y] > 0)
        {
            break;
        }
        map[x + 1][y] = map[x][y] + 1;
        x++;
    }

    x = start_x;
    y = start_y;
    while (y > 0)
    {
        if (map[x][y - 1] == -1 || map[x][y - 1] > 0)
        {
            break;
        }
        map[x][y - 1] = map[x][y] + 1;
        y--;
    }

    y = start_y;
    while (y < map_height - 1)
    {
        if (map[x][y + 1] == -1 || map[x][y + 1] > 0)
        {
            break;
        }
        map[x][y + 1] = map[x][y] + 1;
        y++;
    }

    x = start_x;
    y = start_y;
    while (x > 0 && y > 0)
    {
        if (map[x - 1][y - 1] == -1 || map[x - 1][y - 1] > 0)
        {
            break;
        }
        map[x - 1][y - 1] = map[x][y] + 1;
        x--;
        y--;
    }

    x = start_x;
    y = start_y;
    while (x < map_width - 1 && y < map_height - 1)
    {
        if (map[x + 1][y + 1] == -1 || map[x + 1][y + 1] > 0)
        {
            break;
        }
        map[x + 1][y + 1] = map[x][y] + 1;
        x++;
        y++;
    }

    x = start_x;
    y = start_y;
    while (x < map_width - 1 && y > 0)
    {
        if (map[x + 1][y - 1] == -1 || map[x + 1][y - 1] > 0)
        {
            break;
        }
        map[x + 1][y - 1] = map[x][y] + 1;
        x++;
        y--;
    }

    x = start_x;
    y = start_y;
    while (x > 0 && y < map_height - 1)
    {
        if (map[x - 1][y + 1] == -1 || map[x - 1][y + 1] > 0)
        {
            break;
        }
        map[x - 1][y + 1] = map[x][y] + 1;
        x--;
        y++;
    }
}

static void running_wave()
{
    int min = 1;
    int max;

    if (map_width > map_height)
    {
        max = map_width;
    }
    else
    {
        max = map_height;
    }
    running_wave_one(start_x, start_y);
    min++;
    for (int i = 0; i < max; i++)
    {
        for (int j = 0; j < map_height; j++)
        {
            for (int k = 0; k < map_width; k++)
            {
                if (map[j][k] == min)
                {
                    running_wave_one(j, k);
                }
            }
        }
        min++;
    }
}

void get_site_min(int x, int y, int *minx, int *miny, int lastx, int lasty)
{
    int min = 0;

    if (x > 0)
    {
        if (map[x - 1][y] > 0 && (min > map[x - 1][y] || min == 0))
        {
            if (x - 1 != lastx && y != lasty)
            {
                min = map[x - 1][y];
                *minx = x - 1;
                *miny = y;
            }
        }

        if (y > 0)
        {
            if (map[x][y - 1] > 0 && ((min > map[x][y - 1] || min == 0)))
            {
                if (x != lastx && y - 1 != lasty)
                {
                    min = map[x][y - 1];
                    *minx = x;
                    *miny = y - 1;
                }
            }
            if (map[x - 1][y - 1] > 0 && (min > map[x - 1][y - 1] || min == 0))
            {
                if (x - 1 != lastx && y - 1 != lasty)
                {
                    min = map[x - 1][y - 1];
                    *minx = x - 1;
                    *miny = y - 1;
                }
            }
        }

        if (y < map_height - 1)
        {
            if (map[x - 1][y + 1] > 0 && (min > map[x - 1][y + 1] || min == 0))
            {
                if (x - 1 != lastx && y + 1 != lasty)
                {
                    min = map[x - 1][y + 1];
                    *minx = x - 1;
                    *miny = y + 1;
                }
            }
        }
    }

    if (x < map_width - 1)
    {
        if (map[x + 1][y] > 0 && (min > map[x + 1][y] || min == 0))
        {
            if (x + 1 != lastx && y != lasty)
            {
                min = map[x + 1][y];
                *minx = x + 1;
                *miny = y;
            }
        }

        if (y > 0)
        {
            if (map[x + 1][y - 1] > 0 && (min > map[x + 1][y - 1] || min == 0))
            {
                if (x - 1 != lastx && y != lasty)
                {
                    min = map[x - 1][y];
                    *minx = x + 1;
                    *miny = y - 1;
                }
            }
        }

        if (y < map_height - 1)
        {
            if (map[x + 1][y + 1] > 0 && (min > map[x + 1][y + 1] || min == 0))
            {
                if (x + 1 != lastx && y + 1 != lasty)
                {
                    min = map[x + 1][y + 1];
                    *minx = x + 1;
                    *miny = y + 1;
                }
            }
        }
    }
}

void output_file()
{
    FILE *fp = fopen("wave.txt", "a+");
    if (NULL == fp)
    {
        return;
    }

    fprintf(fp, "Result array:");

    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            fprintf(fp, "%c ", wave_map[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}
void get_wave_path()
{
    wave_map = (char **)malloc(sizeof(char *) * map_height);
    if (NULL == wave_map)
    {
        return;
    }
    for (int i = 0; i < map_height; i++)
    {
        wave_map[i] = malloc(sizeof(char) * map_width);
        if (NULL == wave_map[i])
        {
            free_wave_map();
            return;
        }
    }

    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            if (map[i][j] == -1)
            {
                wave_map[i][j] = '#';
            }
            else
            {
                wave_map[i][j] = ' ';
            }
        }
    }


    int x = start_x;
    while (x < goal_x)
    {
        if (map[x][start_y] != -1)
        {
            wave_map[x][start_y] = '*';
        }
        x++;
    }

    x = start_x;
    while (x > goal_x)
    {
        if (map[x][start_y] != -1)
        {
            wave_map[x][start_y] = '*';
        }
        x--;
    }


    int y = start_y;
    while (y < goal_y)
    {
        if (map[x][y] != -1)
        {
            wave_map[goal_x][y] = '*';
           
        }
        y++;
    }

    y = start_y;
    while (y > goal_y)
    {
        if (map[x][y] != -1)
        {
            wave_map[goal_x][y] = '*';
            
        }
        y--;
    }

    wave_map[start_x][start_y] = '@';
    wave_map[goal_x][goal_y] = '$';

    output_file();
}

int main(int argc, char **argv)
{
    int ret;
    printf("Welcome to Baozan Yan's CSE240 WaveFront Pather\n");
    if (argc == 3)
    {
        if (strcmp(argv[1], "-f") != 0)
        {
            return -1;
        }
        ret = file_init(argv[2]);
    }
    else
    {
        ret = input_init();
    }

    if (ret < 0)
    {
        return 0;
    }
    PrintEnvironment(map, map_width, map_height);

    while (1)
    {
        get_goal_site();
        if (map[goal_x][goal_y] == -1)
        {
            printf("Sorry, that position is inside an obstacle\n");
            continue;
        }
        break;
    }

    while (1)
    {
        get_start_site();
        if (map[start_x][start_y] == -1)
        {
            printf("Sorry, that position is inside an obstacle\n");
            continue;
        }
        break;
    }
    map[start_x][start_y] = 1;

    running_wave();

    PrintEnvironment(map, map_width, map_height);
    get_wave_path();
    free_wave_map();
    free_map();
}
