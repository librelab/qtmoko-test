/*
 * Copyright 2009, 2010 Thierry Vuillaume
 *
 * This file is part of NeronGPS.
 *
 * NeronGPS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * NeronGPS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with NeronGPS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef GPXBUILDER_H
#define GPXBUILDER_H

#include <QObject>
#include <QFile>
#include <QStringList>

#include "include/thread.h"

#define GPXBUILDER_TRANSFERSIZE		2048

class TGpxBuilder : public TThread
{
	Q_OBJECT
	public:
		TGpxBuilder(QString outputFile, QStringList &inputFiles);
		~TGpxBuilder();

		void run();

	private:
		QString _outputFile;
		QStringList _inputFiles;

		void writeFile(QFile &file);
		bool transferFile(QFile &file, QString &inputName);
		void transferFile(QFile &output, QFile &input);
		void writeHeader(QFile &file);
		void writeFooter(QFile &file);
};

#endif

