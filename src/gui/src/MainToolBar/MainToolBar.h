/*
 * Hydrogen
 * Copyright(c) 2002-2008 by Alex >Comix< Cominu [comix@users.sourceforge.net]
 * Copyright(c) 2008-2026 The hydrogen development team [hydrogen-devel@lists.sourceforge.net]
 *
 * http://www.hydrogen-music.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see
 * https://www.gnu.org/licenses
 *
 */

#ifndef MAIN_TOOL_BAR_H
#define MAIN_TOOL_BAR_H

#include <core/AudioEngine/AudioEngine.h>
#include <core/Midi/MidiAction.h>
#include "../Widgets/EditorDefs.h"
#include "../EventListener.h"

#include <QAction>
#include <QActionGroup>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QToolBar>
#include <QToolButton>

class BpmSpinBox;
class BpmTap;
class LCDDisplay;
class MidiControlButton;
class MidiControlDialog;
class MidiLearnableToolButton;

class MainToolBar : public QToolBar, public EventListener {
	Q_OBJECT

public:
	explicit MainToolBar( QWidget* pParent );
	~MainToolBar();

	void setInput( Editor::Input input );
	Editor::Input getInput() const { return m_input; }
	void setMidiControlDialogVisible( bool bVisible );
	void setPreferencesVisibilityState( bool bChecked );
	MidiControlDialog* getMidiControlDialog() const { return m_pMidiControlDialog; }
	void updateActions();

	void audioDriverChangedEvent() override;
	void beatCounterEvent() override;
	void jackTimebaseStateChangedEvent( int nState ) override;
	void jackTransportActivationEvent() override;
	void loopModeActivationEvent() override;
	void metronomeEvent( int nValue ) override;
	void midiClockActivationEvent() override;
	void recordingModeChangedEvent() override;
	void songModeActivationEvent() override;
	void stateChangedEvent( const H2Core::AudioEngine::State& state ) override;
	void tempoChangedEvent( int nValue ) override;
	void timelineActivationEvent() override;
	void updateSongEvent( int nValue ) override;

	static constexpr int nHeight = 32;
	static constexpr int nWidgetHeight = 24;
	static constexpr int nFontSize = 13;
	static constexpr int nSpacing = 2;
	static constexpr int nSeparatorWidth = 1;
	static constexpr int nSeparatorHeight = 16;
	static constexpr int nSeparatorMargin = 3;
	static constexpr int nMargin = 3;
	static constexpr int nBorder = 1;

private slots:
	void updateTime();

	void recBtnClicked();
	void playBtnClicked();
	void stopBtnClicked();
	void rewindBtnClicked();
	void fastForwardBtnClicked();

	void bpmChanged( double fNewBpm );
	void rubberbandButtonToggle();

	void jackTransportBtnClicked();
	void jackTimebaseBtnClicked();

	void onPreferencesChanged( const H2Core::Preferences::Changes& changes );

private:
	void activateSongMode( bool bActivate );
	void updateBpmSpinBox();
	void updateIcons();
	void updateInput();
	void updateJackTimebase();
	void updateJackTransport();
	void updateLoopMode();
	void updateRecordMode();
	void updateSongMode();
	void updateStyleSheet();
	void updateTransportControl();

	Editor::Input m_input;

	QAction* m_pSelectAction;
	QAction* m_pDrawAction;

	LCDDisplay* m_pTimeDisplay;

	MidiLearnableToolButton* m_pRwdButton;
	MidiLearnableToolButton* m_pRecButton;
	MidiLearnableToolButton* m_pPlayButton;

	std::shared_ptr<MidiAction> m_pPlayMidiAction;
	std::shared_ptr<MidiAction> m_pCountInMidiAction;

	QAction* m_pPlayAction;
	QAction* m_pCountInAction;
	MidiLearnableToolButton* m_pStopButton;
	MidiLearnableToolButton* m_pFfwdButton;
	QToolButton* m_pSongLoopButton;

	QAction* m_pSongModeAction;
	QAction* m_pPatternModeAction;
	QAction* m_pGenerativeSwapAction;

	MidiLearnableToolButton* m_pMetronomeButton;
	BpmSpinBox* m_pBpmSpinBox;

	BpmTap* m_pBpmTap;

	QAction* m_pRubberBandAction;
	QAction* m_pRubberBandSeparator;

	MidiControlButton* m_pMidiControlButton;
	MidiControlDialog* m_pMidiControlDialog;

	QAction* m_pJackTransportAction;
	MidiLearnableToolButton* m_pJackTimebaseButton;
	QAction* m_pJackTimebaseAction;
	QAction* m_pJackSeparator;

	QAction* m_pShowPlaylistEditorAction;
	QAction* m_pShowDirectorAction;
	QAction* m_pShowMixerAction;
	QAction* m_pShowRackAction;
	QAction* m_pShowAutomationAction;
	QAction* m_pShowPlaybackTrackAction;
	QAction* m_pShowPreferencesAction;

	QTimer* m_pTimer;

	QString m_sLCDBPMSpinboxToolTip;
	QString m_sLCDBPMSpinboxTimelineToolTip;
	QString m_sLCDBPMSpinboxJackTimebaseToolTip;
};

#endif  // MAIN_TOOL_BAR_H
