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

#ifndef RESOURCESMODEL_H
#define RESOURCESMODEL_H

#include <QAbstractTableModel>
#include <QSet>

class Resource;
class QXmlStreamWriter;
class QXmlStreamReader;

/*************************************************************************************************/
/**************************** Table model containing all resources *******************************/
/*************************************************************************************************/

class ResourcesModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  ResourcesModel();                                                // constructor
  ~ResourcesModel();                                               // destructor

  void           initialise();                                     // create initial default contents
  int            number();                                         // return number of resources in plan
  void           saveToStream( QXmlStreamWriter* );                // write resources data to xml stream
  void           loadFromStream( QXmlStreamReader* );              // load resources data from xml stream

  Resource*      resource( int n );                                // return pointer to n'th resource
  int            index( Resource* r )
                      { return m_resources.indexOf(r); }           // return index of resource, or -1

  bool           initialsIsDuplicate( const QString&, int );       // return if initials is a repeat
  void           emitDataChangedRow( int );                        // emit data changed signal for row
  void           setOverride( QModelIndex i, QVariant v )
                   { m_overrideIndex = i; m_overrideValue = v; }   // set model override values

  void           updateAssignable();                               // determine assignable list
  QSet<Resource*> resourceSet( QString );                          // return set of resources that have tag
  bool           isAssignable( const QString& tag ) const
                   { return m_assignable.contains( tag ); }        // is tag assignable?

  /********************* methods to support QAbstractTableModel ************************/

  int            rowCount( const QModelIndex& parent = QModelIndex() ) const;     // implement virtual row count
  int            columnCount( const QModelIndex& parent = QModelIndex() ) const;  // implement virtual column count
  QVariant       data( const QModelIndex&, int ) const;                           // implement virtual return data
  bool           setData( const QModelIndex&, const QVariant&, int );             // implement virtual set data
  QVariant       headerData( int, Qt::Orientation, int ) const;                   // implement virtual header data
  Qt::ItemFlags  flags( const QModelIndex& ) const;                               // implement virtual return flags

public slots:
  void           slotCalendarNameChange();                         // slot to receive calendar name changed signal

signals:
  void         nameChanged() const;                                // signal that a day name has changed
  void         editCell( const QModelIndex&,
                         const QString& ) const;                   // signal that cell editing needs to continue
private:
  QList<Resource*>  m_resources;       // list of resources available to plan
  QSet<QString>     m_assignable;      // set of assignable resource tag(s)

  QModelIndex       m_overrideIndex;   // with value can override model for edits in progress
  QVariant          m_overrideValue;   // with index can override model for edits in progress
};

#endif // RESOURCESMODEL_H
