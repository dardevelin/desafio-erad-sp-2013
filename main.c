#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_W 7680
#define MAX_H 4320
#define BORDER 2

static uint16_t width, height;
static uint8_t img[500000000] = {0,}; /* Aloca 0.5 GB */
static uint8_t out[500000000] = {0,}; /* Aloca 0.5 GB */

void smooth5()
{
	int w = width + 2*BORDER;
	int i, j;
	int r, g, b, a;
	for (i = BORDER; i < height + BORDER; i++) {
		for (j = BORDER; j < width + BORDER; j++) {
			r = g = b = a = 0;

			r += img[((i-2)*w + (j-2))*4+0], g += img[((i-2)*w + (j-2))*4+1], b += img[((i-2)*w + (j-2))*4+2], a += img[((i-2)*w + (j-2))*4+3];
			r += img[((i-2)*w + (j-1))*4+0], g += img[((i-2)*w + (j-1))*4+1], b += img[((i-2)*w + (j-1))*4+2], a += img[((i-2)*w + (j-1))*4+3];
			r += img[((i-2)*w + (j+0))*4+0], g += img[((i-2)*w + (j+0))*4+1], b += img[((i-2)*w + (j+0))*4+2], a += img[((i-2)*w + (j+0))*4+3];
			r += img[((i-2)*w + (j+1))*4+0], g += img[((i-2)*w + (j+1))*4+1], b += img[((i-2)*w + (j+1))*4+2], a += img[((i-2)*w + (j+1))*4+3];
			r += img[((i-2)*w + (j+2))*4+0], g += img[((i-2)*w + (j+2))*4+1], b += img[((i-2)*w + (j+2))*4+2], a += img[((i-2)*w + (j+2))*4+3];

			r += img[((i-1)*w + (j-2))*4+0], g += img[((i-1)*w + (j-2))*4+1], b += img[((i-1)*w + (j-2))*4+2], a += img[((i-1)*w + (j-2))*4+3];
			r += img[((i-1)*w + (j-1))*4+0], g += img[((i-1)*w + (j-1))*4+1], b += img[((i-1)*w + (j-1))*4+2], a += img[((i-1)*w + (j-1))*4+3];
			r += img[((i-1)*w + (j+0))*4+0], g += img[((i-1)*w + (j+0))*4+1], b += img[((i-1)*w + (j+0))*4+2], a += img[((i-1)*w + (j+0))*4+3];
			r += img[((i-1)*w + (j+1))*4+0], g += img[((i-1)*w + (j+1))*4+1], b += img[((i-1)*w + (j+1))*4+2], a += img[((i-1)*w + (j+1))*4+3];
			r += img[((i-1)*w + (j+2))*4+0], g += img[((i-1)*w + (j+2))*4+1], b += img[((i-1)*w + (j+2))*4+2], a += img[((i-1)*w + (j+2))*4+3];

			r += img[((i-0)*w + (j-2))*4+0], g += img[((i-0)*w + (j-2))*4+1], b += img[((i-0)*w + (j-2))*4+2], a += img[((i-0)*w + (j-2))*4+3];
			r += img[((i-0)*w + (j-1))*4+0], g += img[((i-0)*w + (j-1))*4+1], b += img[((i-0)*w + (j-1))*4+2], a += img[((i-0)*w + (j-1))*4+3];
			r += img[((i-0)*w + (j+0))*4+0], g += img[((i-0)*w + (j+0))*4+1], b += img[((i-0)*w + (j+0))*4+2], a += img[((i-0)*w + (j+0))*4+3];
			r += img[((i-0)*w + (j+1))*4+0], g += img[((i-0)*w + (j+1))*4+1], b += img[((i-0)*w + (j+1))*4+2], a += img[((i-0)*w + (j+1))*4+3];
			r += img[((i-0)*w + (j+2))*4+0], g += img[((i-0)*w + (j+2))*4+1], b += img[((i-0)*w + (j+2))*4+2], a += img[((i-0)*w + (j+2))*4+3];

			r += img[((i+1)*w + (j-2))*4+0], g += img[((i+1)*w + (j-2))*4+1], b += img[((i+1)*w + (j-2))*4+2], a += img[((i+1)*w + (j-2))*4+3];
			r += img[((i+1)*w + (j-1))*4+0], g += img[((i+1)*w + (j-1))*4+1], b += img[((i+1)*w + (j-1))*4+2], a += img[((i+1)*w + (j-1))*4+3];
			r += img[((i+1)*w + (j+0))*4+0], g += img[((i+1)*w + (j+0))*4+1], b += img[((i+1)*w + (j+0))*4+2], a += img[((i+1)*w + (j+0))*4+3];
			r += img[((i+1)*w + (j+1))*4+0], g += img[((i+1)*w + (j+1))*4+1], b += img[((i+1)*w + (j+1))*4+2], a += img[((i+1)*w + (j+1))*4+3];
			r += img[((i+1)*w + (j+2))*4+0], g += img[((i+1)*w + (j+2))*4+1], b += img[((i+1)*w + (j+2))*4+2], a += img[((i+1)*w + (j+2))*4+3];

			r += img[((i+2)*w + (j-2))*4+0], g += img[((i+2)*w + (j-2))*4+1], b += img[((i+2)*w + (j-2))*4+2], a += img[((i+2)*w + (j-2))*4+3];
			r += img[((i+2)*w + (j-1))*4+0], g += img[((i+2)*w + (j-1))*4+1], b += img[((i+2)*w + (j-1))*4+2], a += img[((i+2)*w + (j-1))*4+3];
			r += img[((i+2)*w + (j+0))*4+0], g += img[((i+2)*w + (j+0))*4+1], b += img[((i+2)*w + (j+0))*4+2], a += img[((i+2)*w + (j+0))*4+3];
			r += img[((i+2)*w + (j+1))*4+0], g += img[((i+2)*w + (j+1))*4+1], b += img[((i+2)*w + (j+1))*4+2], a += img[((i+2)*w + (j+1))*4+3];
			r += img[((i+2)*w + (j+2))*4+0], g += img[((i+2)*w + (j+2))*4+1], b += img[((i+2)*w + (j+2))*4+2], a += img[((i+2)*w + (j+2))*4+3];

			out[(i*w + j)*4 + 0] = r / 25;
			out[(i*w + j)*4 + 1] = g / 25;
			out[(i*w + j)*4 + 2] = b / 25;
			out[(i*w + j)*4 + 3] = a / 25;
		}
	}
}

void load()
{
	int i;
	int file = open("image.in", O_RDONLY);

	if (file == -1) {
		perror("open");
		exit(1);
	}

	read(file, &width, sizeof(width));
	read(file, &height, sizeof(height));

	for (i = BORDER; i < height + BORDER; i++)
		read(file, &img[(i*(width+BORDER*2) + BORDER)*4], width*4);
}

void store()
{
	int i;
	int file = creat("image.out", 0644);

	write(file, &width, sizeof(width));
	write(file, &height, sizeof(height));

	for (i = BORDER; i < height + BORDER; i++)
		write(file, &out[(i*(width+BORDER*2) + BORDER)*4], width*4);
}

int main(int argc, char *argv[])
{
	load();
	smooth5();
	store();
	return 0;
}
