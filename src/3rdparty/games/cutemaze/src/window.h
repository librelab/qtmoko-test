/***********************************************************************
 *
 * Copyright (C) 2007-2008 Graeme Gott <graeme@gottcode.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
class Board;
class Scores;
class Settings;
class QAction;

class Window : public QMainWindow
{
public:
	Window(QWidget *parent = 0, Qt::WindowFlags wf = 0);

	virtual bool eventFilter(QObject* watched, QEvent* event);

protected:
	virtual void closeEvent(QCloseEvent* event);

private:
	void initMenuBar();
	void initToolBar();

	Board* m_board;
	Scores* m_scores;
	Settings* m_settings;
	QAction* m_pause_action;
	int m_pause_count;
	bool m_was_paused;
	bool m_pause_available;
};

#endif // WINDOW_H
