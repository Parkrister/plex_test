#include "Plex.h"
TRoot::TRoot()
{
	visible = false;
	active = false;
}
bool TRoot::IsVisible()
{
	return visible;
}
bool TRoot::IsActive()
{
	return active;
}
TPoint::TPoint(int x1, int y1)
{
	if (x1 < 0 || y1 < 0)
		throw - 1;
	x = x1;
	y = y1;
}
void TPoint::SetX(int val) {
	if (val < 0)
		throw - 1;
	x = val;
}
void TPoint::SetY(int val) {
	if (val < 0)
		throw - 1;
	y = val;
}
int TPoint::GetX() const {
	return x;
}
int TPoint::GetY() const {
	return y;
}
void TPoint::show(Graphics^ gr)
{
	gr->DrawLine(Pens::Black, max(0, x - 2), max(0, y - 2), x+2, y+2);
	visible = true;
}
void TPoint:: hide(Graphics ^ gr)
{
	gr->DrawLine(Pens::White, max(0, x - 2), max(0, y - 2), x+2, y+2);
	visible = true;
}
TChart::TChart():TRoot()
{
	pFirst = NULL;
	pLast = NULL;
}
int TChart::GetSize() {
	int size = 0;
	if (pFirst)
		size++;
	if (pLast)
		size++;
	return size;
}
void TChart::SetFirst(TRoot* p)
{
	TPoint* pPoint = dynamic_cast<TPoint*>(p);
	TChart* pChart = dynamic_cast<TChart*>(p);
	if (pPoint || pChart)
		pFirst = p;
}
void TChart::SetLast(TRoot* p)
{
	TPoint* pPoint = dynamic_cast<TPoint*>(p);
	TChart* pChart = dynamic_cast<TChart*>(p);
	if (pPoint || pChart)
		pLast = p;
}
void TChart::show(Graphics^ gr)
{
	TLine CurrLine;
}