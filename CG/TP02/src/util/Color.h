/*
 * Color.h
 *
 *  Created on: Nov 8, 2014
 *      Author: gustavo
 */

#ifndef UTIL_COLOR_H_
#define UTIL_COLOR_H_

#define RED 0
#define GREEN 1
#define BLUE 2
#define WHITE 3
#define YELLOW 4

#define RGB_LIMIT 255

class Color {
public:

	Color();
	Color(int color);
	virtual ~Color();

	void changeColor(int color);

	/* get values */
	float getRed();
	float getGreen();
	float getBlue();

private:
	int red;
	int green;
	int blue;

};

#endif /* UTIL_COLOR_H_ */
