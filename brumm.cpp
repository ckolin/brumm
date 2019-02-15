#include <bits/stdc++.h>
#include "tgaimage.h"
using namespace std;

const TGAColor white(255);
const TGAColor black(0);

vector<vector<bool>> random_dots(int width, int height) {
	vector<vector<bool>> out(width, vector<bool>(height));
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			out[x][y] = rand() & 1;
	return out;
}

int main(int argc, const char *argv[]) {
	if (argc < 3) {
		cout << "usage: <depthmap> <output>" << "\n";
		return 1;
	}

	const char* depthmap_path = argv[1];
	const char* output_path = argv[2];

	TGAImage depthmap;
	depthmap.read_tga_file(depthmap_path);
	
	int width = depthmap.get_width(), height = depthmap.get_height();
	TGAImage image(width, height, TGAImage::GRAYSCALE);

	int pattern_width = width / 10;
	vector<vector<bool>> dots = random_dots(pattern_width, height);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int ox = depthmap.get(x, y)[0] * pattern_width / 1000;
			dots[x % pattern_width][y] = dots[(x + ox) % pattern_width][y];
			
			image.set(x, y,
				dots[(x + ox) % pattern_width][y] ? white : black);
		}
	}

	image.write_tga_file(output_path);
}
