/********************************************************************
 * inplaceEditor.cpp
 ********************************************************************
 * This file is part of Bungeni Transcribe
 *
 * Copyright (C) 2009 - UNDESA <www.parliaments.info>
 *
 *
 * Author - Miano Njoka <miano@parliaments.info>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 ***********************************************************************/
 
 

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "inplaceEditor.hpp"
#include "transcribeWidget.hpp"

#include <QHBoxLayout>
#include <QGroupBox>
InplaceEditor::InplaceEditor(QWidget * parent) : QWidget(parent)
{
    ui.setupUi(this);
    //TranscribeWidget *transcribe = static_cast<TranscribeWidget*>(parent);
   // p_intf = transcribe->getp_intf();
    horizontalSlider = new QxtSpanSlider();
    horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
    horizontalSlider->setOrientation(Qt::Horizontal);
    horizontalSlider->setMaximum(10000);
    ui.gridLayout->addWidget(horizontalSlider, 2, 3, 1, 2);
    
    speechText = new customTextEdit(parent);
    //speechText->setGeometry(0,0,444,326);
    speechText->setObjectName(QString::fromUtf8("speech"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(3);
    sizePolicy.setHeightForWidth(speechText->sizePolicy().hasHeightForWidth());
    speechText->setSizePolicy(sizePolicy);
    ui.gridLayout->addWidget(speechText, 6, 0, 1, 6);
    
    QObject::connect(ui.startTime, SIGNAL(timeChanged( const QTime & )), this, SLOT(updateStartTime( const QTime &)));
    QObject::connect(ui.endTime, SIGNAL(timeChanged( const QTime & )), this, SLOT(updateEndTime( const QTime &)));
    QObject::connect(horizontalSlider, SIGNAL( lowerValueChanged( int ) ), this, SLOT( updateStartTime( int ) ));
    QObject::connect(horizontalSlider, SIGNAL( upperValueChanged( int ) ), this, SLOT( updateEndTime( int ) ));  
    
  //  QObject::connect( horizontalSlider, SIGNAL(lowerValueChanged( int )), THEMIM->getIM(), SLOT(sliderUpdate( int ) ));
  //  QObject::connect( horizontalSlider, SIGNAL(upperValueChanged( int )), THEMIM->getIM(), SLOT(sliderUpdate( int ) ));
    
    QObject::connect( ui.bold, SIGNAL(clicked( )), this, SLOT( bold( ) ) );
    QObject::connect( ui.italics, SIGNAL(clicked( )), this, SLOT( italics( ) ) );
    QObject::connect( ui.underline, SIGNAL(clicked( )), this, SLOT( underline( ) ) );
    QObject::connect( ui.save, SIGNAL(clicked( )), this, SLOT( save( ) ) );
    QObject::connect( ui.cancel, SIGNAL(clicked( )), this, SLOT( cancel( ) ) );
}

InplaceEditor::~InplaceEditor()
{}
/*
void InplaceEditor::setValues(QString _name, QString _speech, int _startTime, int _endTime)
{
    ui.name->setText(_name);
    speechText->setText(_speech);
}
*/

void InplaceEditor::updateEndTime( const QTime & time )
{
	int temp;
	temp = time.hour() * 3600 + time.minute()*60 + time.second();
	horizontalSlider->setUpperValue(temp);
}

void InplaceEditor::updateStartTime( const QTime & time )
{
	int temp;
	temp = time.hour() * 3600 + time.minute()*60 + time.second();
	horizontalSlider->setLowerValue(temp);
}

void InplaceEditor::updateStartTime( int time )
{
	//int hours, minutes, seconds;
	QString temp;
	QTime start;
	QString timeText = "";
	timeText = InplaceEditor::timeSecondstoString(time);
	start = QTime::fromString(timeText);
	ui.startTime->setTime(start);
	
}

void InplaceEditor::updateEndTime( int time )
{
	//int hours, minutes, seconds;
	QString temp;
	QTime end;
	QString timeText = "";
	timeText = InplaceEditor::timeSecondstoString(time);
	end = QTime::fromString(timeText);
	ui.endTime->setTime(end);
}

//Converts number of seconds into time in this format hh:mm:ss
QString InplaceEditor::timeSecondstoString(int time)
{

	int hours, minutes, seconds;
	QString temp;
	hours = time / 3600;
	minutes = (time % 3600) / 60;
	seconds = (time % 3600) % 60;
	
QString timeText = "";

if (hours < 10)
	{
		timeText.append("0"); 
		temp.setNum(hours);
		timeText += temp;
	}
	else
	{
		temp.setNum(hours);
		timeText += temp;
	}
	if ( minutes < 10 )
	{
		timeText.append(":0"); 
		temp.setNum(minutes);
		timeText += temp;
	}
	else
	{
		temp.setNum(minutes);
		timeText += ":"+temp;
	}
	if ( seconds < 10 )
	{
		timeText.append(":0"); 
		temp.setNum(seconds);
		timeText += temp;
	}
	else
	{
		temp.setNum(seconds);
		timeText += ":" + temp;
	}
	return timeText;

}

void InplaceEditor::bold()
{
    QTextCursor cursor(speechText->textCursor());
    QTextCharFormat format;
    if (cursor.charFormat().fontItalic()==true)
    {    
        format.setFontItalic(true);
    }
    if (cursor.charFormat().fontUnderline()==true)
    {    
        format.setFontUnderline(true);
    }
    if (cursor.charFormat().fontWeight()==QFont::Bold)
    {    
        format.setFontWeight(QFont::Light);     
    }
    else
    {
        format.setFontWeight(QFont::Bold);
    }
    cursor.setCharFormat(format);
}

void InplaceEditor::underline()
{
    QTextCursor cursor(speechText->textCursor());
    QTextCharFormat format;
    if (cursor.charFormat().fontItalic()==true)
    {    
        format.setFontItalic(true);
    }
    if (cursor.charFormat().fontWeight()==QFont::Bold)
    {    
        format.setFontWeight(QFont::Bold);     
    }
    if (cursor.charFormat().fontUnderline()==true)
    {    
        format.setFontUnderline(false);
    }
    else
    {
        format.setFontUnderline(true);
    }
    cursor.setCharFormat(format);
}

void InplaceEditor::italics()
{
    QTextCursor cursor(speechText->textCursor());
    QTextCharFormat format;
    if (cursor.charFormat().fontUnderline()==true)
    {    
        format.setFontUnderline(true);
    }
    if (cursor.charFormat().fontWeight()==QFont::Bold)
    {    
        format.setFontWeight(QFont::Bold);     
    }
    if (cursor.charFormat().fontItalic()==true)
    {    
        format.setFontItalic(false);
    }
    else
    {
        format.setFontItalic(true);
    }
    cursor.setCharFormat(format);
}

void InplaceEditor::save()
{
    emit close(this);
    emit closeIndex(index);
}

void InplaceEditor::cancel()
{
    emit cancelled(this);
    emit closeIndex(index);
}

void InplaceEditor::setIndex(const QModelIndex & index_)
{
    this->index = index_;
}


QString InplaceEditor::getName()
{
    return ui.name->text();
}


QString InplaceEditor::getSpeech()
{
    //return ui.speech->toPlainText();
    return speechText->toHtml();
}


QTime InplaceEditor::getStartTime()
{
    return ui.startTime->time();
}
    
QTime InplaceEditor::getEndTime()
{
    return ui.endTime->time();
}

bool InplaceEditor::getComplete()
{
    if ( ui.incomplete->isChecked())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void InplaceEditor::setName(QString name)
{
    ui.name->setText(name);
}

void InplaceEditor::setComplete(bool incomplete)
{
    if (incomplete)
    {
        ui.incomplete->setCheckState(Qt::Checked);
    }
    else
    {
        ui.incomplete->setCheckState(Qt::Unchecked);
    }
}
 
void InplaceEditor::setSpeech(QString speech)
{
   // ui.speech->setText(speech);
   speechText->setHtml(speech);
}
    
void InplaceEditor::setStartTime(int start)
{
    ui.startTime->setTime(QTime::fromString(InplaceEditor::timeSecondstoString(start)));
}
    
void InplaceEditor::setEndTime(int end)
{
    ui.endTime->setTime(QTime::fromString(InplaceEditor::timeSecondstoString(end)));
}