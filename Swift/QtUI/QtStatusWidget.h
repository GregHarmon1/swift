/*
 * Copyright (c) 2010 Kevin Smith
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include "Swiften/Elements/StatusShow.h"

#include <QWidget>
#include <QMap>
#include <QIcon>

class QComboBox;
class QLabel;
class QStackedWidget;
class QListWidget;
class QListWidgetItem;

namespace Swift {
	class QtLineEdit;
	class QtStatusWidget : public QWidget {
		Q_OBJECT
		public:
			QtStatusWidget(QWidget *parent);
			~QtStatusWidget();
			StatusShow::Type getSelectedStatusShow();
			void setStatusType(StatusShow::Type type);
		signals:
			void onChangeStatusRequest(StatusShow::Type showType, const QString& text);
		public slots:
			void setStatusText(const QString& text);
		private slots:
			void generateList();
			void handleClicked();
			void handleEditComplete();
			void handleEditCancelled();
			void handleApplicationFocusChanged(QWidget* old, QWidget* now);
		protected slots:
			virtual void mousePressEvent(QMouseEvent* event);
			void handleItemClicked(QListWidgetItem* item);
		private:
			void viewMode();
			//QComboBox *types_;
			QStackedWidget* stack_;
			QLabel* statusIcon_;
			QLabel* statusTextLabel_;
			QtLineEdit* statusEdit_;
			QString statusText_;
			QString newStatusText_;
			QMap<StatusShow::Type, QIcon> icons_;
			StatusShow::Type selectedStatusType_;
			bool isClicking_;
			QListWidget* menu_;
			QCursor editCursor_;
			QCursor viewCursor_;
			bool editing_;
	};
}

