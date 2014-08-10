/***************************************************************************
 *   Copyright (C) 2014 by Richard Crook                                   *
 *   http://code.google.com/p/projectplanner                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "datetime.h"

/*************************************************************************************************/
/********************** XTime provides static methods to support Time type ***********************/
/*************************************************************************************************/

/********************************************* time **********************************************/

Time XTime::time( int hours, int mins )
{
  // return qint16 Time from hours & minutes
  Q_ASSERT( hours >= 0 );
  Q_ASSERT( hours <= 24 );
  Q_ASSERT( mins >= 0 );
  Q_ASSERT( mins <= 59 );
  Q_ASSERT( hours < 24 || mins == 0 );
  return hours*60 + mins;
}

Time XTime::time( QString str )
{
  // return time from string "hh:mm" format
  int hours = str.left(2).toInt();
  int mins  = str.right(2).toInt();
  return hours*60 + mins;
}

/******************************************* toString ********************************************/

QString XTime::toString( Time t )
{
  // return HH:MM string from Time
  if ( t == XTime::NULL_TIME ) return QString( "Null" );

  Q_ASSERT( t >= 0 );
  Q_ASSERT( t <= 24*60 );
  return QString( "%1:%2" ).arg( t/60, 2, 10, QLatin1Char('0') )
                           .arg( t%60, 2, 10, QLatin1Char('0') );
}

/*************************************************************************************************/
/********************** XDate provides static methods to support Date type ***********************/
/*************************************************************************************************/

const QDate  XDate::ANCHOR_QDATE  = QDate( 1, 1, 1 );
const qint64 XDate::ANCHOR_JULIAN = XDate::ANCHOR_QDATE.toJulianDay();

const QDate  XDate::MIN_QDATE = XDate::ANCHOR_QDATE;
const QDate  XDate::MAX_QDATE = QDate( 7999, 12, 31 );
const Date   XDate::MIN_DATE  = XDate::date( XDate::MIN_QDATE );
const Date   XDate::MAX_DATE  = XDate::date( XDate::MAX_QDATE );

/********************************************* date **********************************************/

Date XDate::date( int year, int mon, int day )
{
  // return qint32 Date from year, month, day
  Q_ASSERT( year >= 1 );
  Q_ASSERT( year <= 8000 );
  Q_ASSERT( mon >= 1 );
  Q_ASSERT( mon <= 12 );
  Q_ASSERT( day >= 1 );
  Q_ASSERT( day <= 31 );

  return QDate( year, mon, day ).toJulianDay() - ANCHOR_JULIAN;
}

Date XDate::date( QDate qd )
{
  // return qint32 Date from QDate
  if ( qd.isNull() ) return NULL_DATE;
  return qd.toJulianDay() - ANCHOR_JULIAN;
}

/******************************************** qdate **********************************************/

QDate XDate::qdate( Date d )
{
  // return QDate from qint32 Date
  if ( d == NULL_DATE ) return QDate();
  return ANCHOR_QDATE.addDays( d );
}

/****************************************** currentDate ******************************************/

Date XDate::currentDate()
{
  // return qint32 Date for current date
  return QDate::currentDate().toJulianDay() - ANCHOR_JULIAN;
}

/******************************************* toString ********************************************/

QString XDate::toString( Date d )
{
  // return dd/MM/yyyy string from Date
  return toString( d, "dd/MM/yyyy" );
}

QString XDate::toString( Date d, QString format )
{
  // return string in specified format from Date
  if ( d == XDate::NULL_DATE ) return QString( "NA" );

  QDate qdate = ANCHOR_QDATE.addDays( d );
  return qdate.toString( format );
}

/*************************************************************************************************/
/****************** XDateTime provides static methods to support DateTime type *******************/
/*************************************************************************************************/

const QDateTime  XDateTime::ANCHOR_QDATETIME = QDateTime( XDate::ANCHOR_QDATE );
const QDateTime  XDateTime::MIN_QDATETIME    = QDateTime( XDate::MIN_QDATE );
const QDateTime  XDateTime::MAX_QDATETIME    = QDateTime( XDate::MAX_QDATE ).addSecs( 86340 );
const DateTime   XDateTime::MIN_DATETIME     = XDateTime::datetime( XDateTime::MIN_QDATETIME );
const DateTime   XDateTime::MAX_DATETIME     = XDateTime::datetime( XDateTime::MAX_QDATETIME );

/****************************************** qdatetime ********************************************/

DateTime XDateTime::datetime( QDateTime qdt )
{
  // return quint32 DateTime from QDateTime
  if ( !qdt.isValid() ) return XDateTime::NULL_DATETIME;
  return ANCHOR_QDATETIME.secsTo( qdt ) / 60;
}

/****************************************** qdatetime ********************************************/

QDateTime XDateTime::qdatetime( DateTime dt )
{
  // return QDateTime from quint32 DateTime
  if ( dt == NULL_DATETIME ) return QDateTime();
  return ANCHOR_QDATETIME.addSecs( dt*60 );
}

/****************************************** currentDate ******************************************/

DateTime XDateTime::currentDateTime()
{
  // return quint32 DateTime for current date-time
  return datetime( QDateTime::currentDateTime() );
}

/******************************************* toString ********************************************/

QString XDateTime::toString( DateTime dt )
{
  // return dd/MM/yyyy hh:mm string from DateTime
  return toString( dt, "dd/MM/yyyy hh:mm" );
}

QString XDateTime::toString( DateTime dt, QString format )
{
  // return string in specified format from Date
  if ( dt == XDateTime::NULL_DATETIME ) return QString( "NA" );

  QDateTime qdatetime = ANCHOR_QDATETIME.addSecs( dt*60 );
  return qdatetime.toString( format );
}
