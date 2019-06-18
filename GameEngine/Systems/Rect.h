#pragma once
template <typename T> struct Rect {
private:
	T left;
	T top;
	T right;
	T bottom;
public: 
	T getLeft() {
		return left;
	};
	T getTop() {
		return top;
	};
	T getRight() {
		return right;
	}
	T getBottom() {
		return bottom;
	};
	Rect(T l, T t, T r, T b) {
		left = l;
		top = t;
		right = r;
		bottom = b;
	};
	Rect(const Rect &r2) {
		left = r2->getLeft();
		top = r2->getTop();
		right = r2->getRight();
		bottom = r2->getBottom();
	};
};
