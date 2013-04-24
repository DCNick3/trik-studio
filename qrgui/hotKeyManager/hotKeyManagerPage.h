#pragma once

#include "../dialogs/preferencesPages/preferencesPage.h"

#include <QtGui/QKeySequence>

namespace Ui {
	class hotKeyManagerPage;
}

class PreferencesHotKeyManagerPage : public PreferencesPage
{
	Q_OBJECT
	
public:
	explicit  PreferencesHotKeyManagerPage(QWidget *parent = 0);
	~PreferencesHotKeyManagerPage();

	void save();
	void restoreSettings();

	void mousePressEvent(QMouseEvent *event);

private slots:
	void activateShortcutLineEdit(int const row, int const column);
	void newModifiers(Qt::KeyboardModifiers modifiers);
	void newKey(int const key);

private:
	void loadHotKeys();
	void updateCurrentRow(QString const shortcut);

	Ui::hotKeyManagerPage *mUi;

	int mCurrentRow;
	Qt::KeyboardModifiers mCurrentModifiers;
};
