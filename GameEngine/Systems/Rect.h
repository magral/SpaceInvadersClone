#pragma once
template <typename T> struct Rect {
private:
	T x;
	T y;
	T width;
	T height;
public: 
	T getX() {
		return x;
	};
	T getY() {
		return y;
	};
	T getWidth() {
		return width;
	}
	T getHeight() {
		return height;
	};
	Rect(T x1, T y1, T height, T width) {
		x = x1;
		y = y1;
		this->height = height;
		this->width = width;
	};
	Rect(const Rect &r2) {
		x = r2->getX();
		y = r2->getY();
		height = r2->getHeight();
		width = r2->getWidth();
	};
};
