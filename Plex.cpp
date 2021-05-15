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
	Pen^ pen;
	pen = gcnew Pen(Color::Black);
	pen->Width = 4.f;
	gr->DrawEllipse(pen, x, y, 4, 4);
	visible = true;
}
void TPoint:: hide(Graphics ^ gr)
{
	Pen^ pen;
	pen = gcnew Pen(Color::White);
	pen->Width = 4.f;
	gr->DrawEllipse(pen, x, y, 4, 4);
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
TRoot* TChart::GetFisrt()
{
	return pFirst;
}
TRoot* TChart::GetLast()
{
	return pLast;
}
void TChart::show(Graphics^ gr)
{
	TLine CurrLine;
	TRoot* pr;
	TPoint* pp;
	CurrLine.pChart = this;
	CurrLine.pFp = CurrLine.pLp = NULL;
	while (!st.empty())
	{
		st.pop();
	}
	st.push(CurrLine);
	while (!st.empty())
	{
		CurrLine = st.top();
		st.pop();
		while (!CurrLine.pFp)
		{
			pr = CurrLine.pChart->GetFisrt();
			pp = dynamic_cast<TPoint*>(pr);
			if (pp)
			{
				CurrLine.pFp = pp;
				pp->show(gr);
			}
			else
			{
				st.push(CurrLine);
				CurrLine.pChart = dynamic_cast<TChart*>(pr);
			}
		}
		if (!CurrLine.pLp)
		{
			pr = CurrLine.pChart->GetLast();
			pp = dynamic_cast<TPoint*>(pr);
			if (pp)
			{
				CurrLine.pLp = pp;
				pp->show(gr);
			}
			else
			{
				st.push(CurrLine);
				CurrLine.pChart = dynamic_cast<TChart*>(pr);
				CurrLine.pFp = NULL;
				st.push(CurrLine);
			}
		}
		if (CurrLine.pFp && CurrLine.pLp)
		{
			Pen^ pen;
			pen = gcnew Pen(Color::Black);
			pen->Width = 3.f;
			gr->DrawLine(pen, CurrLine.pFp->GetX(), CurrLine.pFp->GetY(), CurrLine.pLp->GetX(), CurrLine.pLp->GetY());
			pp = CurrLine.pLp;
			if (!st.empty())
			{
				CurrLine = st.top();
				st.pop();
				if (!CurrLine.pFp)
					CurrLine.pFp = pp;
				else
					CurrLine.pLp = pp;
				st.push(CurrLine);
			}
		}
	}
}
void TChart::hide(Graphics^ gr)
{
	TLine CurrLine;
	TRoot* pr;
	TPoint* pp;
	CurrLine.pChart = this;
	CurrLine.pFp = CurrLine.pLp = NULL;
	while (!st.empty())
	{
		st.pop();
	}
	st.push(CurrLine);
	while (!st.empty())
	{
		CurrLine = st.top();
		st.pop();
		while (!CurrLine.pFp)
		{
			pr = CurrLine.pChart->GetFisrt();
			pp = dynamic_cast<TPoint*>(pr);
			if (pp)
			{
				CurrLine.pFp = pp;
				pp->show(gr);
			}
			else
			{
				st.push(CurrLine);
				CurrLine.pChart = dynamic_cast<TChart*>(pr);
			}
		}
		if (!CurrLine.pLp)
		{
			pr = CurrLine.pChart->GetLast();
			pp = dynamic_cast<TPoint*>(pr);
			if (pp)
			{
				CurrLine.pLp = pp;
				pp->show(gr);
			}
			else
			{
				st.push(CurrLine);
				CurrLine.pChart = dynamic_cast<TChart*>(pr);
				CurrLine.pFp = NULL;
				st.push(CurrLine);
			}
		}
		if (CurrLine.pFp && CurrLine.pLp)
		{
			Pen^ pen;
			pen = gcnew Pen(Color::White);
			pen->Width = 3.f;
			gr->DrawLine(pen, CurrLine.pFp->GetX(), CurrLine.pFp->GetY(), CurrLine.pLp->GetX(), CurrLine.pLp->GetY());
			pen = gcnew Pen(Color::White);
			pen->Width = 4.f;
			gr->DrawEllipse(pen, CurrLine.pFp->GetX(), CurrLine.pFp->GetY(), 4, 4);
			gr->DrawEllipse(pen, CurrLine.pLp->GetX(), CurrLine.pLp->GetY(), 4, 4);
			pp = CurrLine.pLp;
			if (!st.empty())
			{
				CurrLine = st.top();
				st.pop();
				if (!CurrLine.pFp)
					CurrLine.pFp = pp;
				else
					CurrLine.pLp = pp;
				st.push(CurrLine);
			}
		}
	}
}
bool TChart::InsLine(TChart* line)
{
	TPoint* first = dynamic_cast<TPoint*>(line->GetFisrt());
	TPoint* last = dynamic_cast<TPoint*>(line->GetLast());
	TLine CurrLine;
	TRoot* pr;
	TPoint* pp;
	CurrLine.pChart = this;
	CurrLine.pFp = CurrLine.pLp = NULL;
	while (!st.empty())
	{
		st.pop();
	}
	st.push(CurrLine);
	while (!st.empty())
	{
		CurrLine = st.top();
		st.pop();
		while (!CurrLine.pFp)
		{
			pr = CurrLine.pChart->GetFisrt();
			pp = dynamic_cast<TPoint*>(pr);
			if (pp)
			{
				CurrLine.pFp = pp;
				if (abs(pp->GetX() - first->GetX()) < 2 && abs(pp->GetY()-first->GetY())<2)
				{
					CurrLine.pChart->SetFirst(line);
					TRoot* tmp = line->GetFisrt();
					line->SetFirst(line->GetLast());
					line->SetLast(tmp);
					return true;
				}
				else if (abs(pp->GetX() - last->GetX()) < 2 && abs(pp->GetY() - last->GetY()) < 2)
				{
					CurrLine.pChart->SetFirst(line);				
					return true;
				}		
			}
			else
			{
				st.push(CurrLine);
				CurrLine.pChart = dynamic_cast<TChart*>(pr);
			}
		}
		if (!CurrLine.pLp)
		{
			pr = CurrLine.pChart->GetLast();
			pp = dynamic_cast<TPoint*>(pr);
			if (pp)
			{
				CurrLine.pLp = pp;
				if ((abs(pp->GetX() - first->GetX()) < 2 && abs(pp->GetY() - first->GetY()) < 2) )
				{
					CurrLine.pChart->SetLast(line);
					TRoot* tmp = line->GetFisrt();
					line->SetFirst(line->GetLast());
					line->SetLast(tmp);
					return true;
				}
				else if (abs(pp->GetX() - last->GetX()) < 2 && abs(pp->GetY() - last->GetY()) < 2)
				{
					CurrLine.pChart->SetLast(line);
					return true;
				}
			}
			else
			{
				st.push(CurrLine);
				CurrLine.pChart = dynamic_cast<TChart*>(pr);
				CurrLine.pFp = NULL;
				st.push(CurrLine);
			}
		}
		if (CurrLine.pFp && CurrLine.pLp)
		{
			pp = CurrLine.pLp;

			if (!st.empty())
			{
				CurrLine = st.top();
				st.pop();

				if (!CurrLine.pFp)
					CurrLine.pFp = pp;
				else
					CurrLine.pLp = pp;
				st.push(CurrLine);
			}
		}
	}
	return false;
}
void TChart::save(std::string filename)
{
	std::ofstream ofs(filename.c_str());
	TLine CurrLine;
	TRoot* pr;
	TPoint* pp;
	CurrLine.pChart = this;
	CurrLine.pFp = CurrLine.pLp = NULL;
	while (!st.empty())
	{
		st.pop();
	}
	st.push(CurrLine);
	while (!st.empty())
	{
		CurrLine = st.top();
		st.pop();
		while (!CurrLine.pFp)
		{
			pr = CurrLine.pChart->GetFisrt();
			pp = dynamic_cast<TPoint*>(pr);
			if (pp)
			{
				CurrLine.pFp = pp;
			}
			else
			{
				st.push(CurrLine);
				CurrLine.pChart = dynamic_cast<TChart*>(pr);
			}
		}
		if (!CurrLine.pLp)
		{
			pr = CurrLine.pChart->GetLast();
			pp = dynamic_cast<TPoint*>(pr);
			if (pp)
			{
				CurrLine.pLp = pp;
			}
			else
			{
				st.push(CurrLine);
				CurrLine.pChart = dynamic_cast<TChart*>(pr);
				CurrLine.pFp = NULL;
				st.push(CurrLine);
			}
		}
		if (CurrLine.pFp && CurrLine.pLp)
		{
			ofs << CurrLine.pFp->GetX() << " " << CurrLine.pFp->GetY() << " " << CurrLine.pLp->GetX() << " " << CurrLine.pLp->GetY() << '\n';
			pp = CurrLine.pLp;
			if (!st.empty())
			{
				CurrLine = st.top();
				st.pop();
				if (!CurrLine.pFp)
					CurrLine.pFp = pp;
				else
					CurrLine.pLp = pp;
				st.push(CurrLine);
			}
		}
	}
	ofs.close();
}
void TChart::read(std::string filename)
{
	std::ifstream ifs(filename.c_str());
	char buff[MAXSIZE];
	while (!ifs.eof())
	{
		TPoint* p1 = new TPoint, * p2 = new TPoint;
		ifs.getline(buff, MAXSIZE, ' ');
		int x1 = atoi(buff);
		ifs.getline(buff, MAXSIZE, ' ');
		int y1 = atoi(buff);
		ifs.getline(buff, MAXSIZE, ' ');
		int x2 = atoi(buff);
		ifs.getline(buff, MAXSIZE, '\n');
		int y2 = atoi(buff);
		p1->SetX(x1);
		p1->SetY(y1);
		p2->SetX(x2);
		p2->SetY(y2);	
		if (!this->GetSize())
		{
			this->SetFirst(p1);
			this->SetLast(p2);
		}
		else
		{
			TChart* line = new TChart;
			line->SetFirst(p1);
			line->SetLast(p2);
			this->InsLine(line);
		}
	}
}