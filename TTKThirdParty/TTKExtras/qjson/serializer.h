/* This file is part of qjson
  *
  * Copyright (C) 2009 Till Adam <adam@kde.org>
  *
  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser General Public
  * License version 2.1, as published by the Free Software Foundation.
  * 
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public License
  * along with this library; see the file COPYING.LIB.  If not, write to
  * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  * Boston, MA 02110-1301, USA.
  */

#ifndef QJSON_SERIALIZER_H
#define QJSON_SERIALIZER_H

#include "ttkprivate.h"
#include "musicextrasglobaldefine.h"

QT_BEGIN_NAMESPACE
class QIODevice;
class QString;
class QVariant;
QT_END_NAMESPACE

namespace QJson {
  /**
   @brief How the indentation should work.
   \verbatim
   none (default) :
            { "foo" : 0, "foo1" : 1, "foo2" : [ { "bar" : 1, "foo" : 0, "foobar" : 0 }, { "bar" : 1, "foo" : 1, "foobar" : 1 } ], "foo3" : [ 1, 2, 3, 4, 5, 6 ] }
  
   compact :
            {"foo":0,"foo1":1,"foo2":[{"bar":1,"foo":0,"foobar":0},{"bar":1,"foo":1,"foobar":1}],"foo3":[1,2,3,4,5,6]}
  
   minimum :
            { "foo" : 0, "foo1" : 1, "foo2" : [
              { "bar" : 1, "foo" : 0, "foobar" : 0 },
              { "bar" : 1, "foo" : 1, "foobar" : 1 }
             ], "foo3" : [
              1,
              2,
              3,
              4,
              5,
              6
             ] }

   medium :
            {
             "foo" : 0, "foo1" : 1, "foo2" : [
              {
               "bar" : 1, "foo" : 0, "foobar" : 0
              },
              {
               "bar" : 1, "foo" : 1, "foobar" : 1
              }
             ], "foo3" : [
              1,
              2,
              3,
              4,
              5,
              6
             ]
            }

   full :
            {
             "foo" : 0,
             "foo1" : 1,
             "foo2" : [
              {
               "bar" : 1,
               "foo" : 0,
               "foobar" : 0
              },
              {
               "bar" : 1,
               "foo" : 1,
               "foobar" : 1
              }
             ],
             "foo3" : [
              1,
              2,
              3,
              4,
              5,
              6
             ]
            }

  
   \endverbatim
  */
  enum IndentMode {
    IndentNone,
    IndentCompact,
    IndentMinimum,
    IndentMedium,
    IndentFull
  };
  /**
  * @brief Main class used to convert QVariant objects to JSON data.
  *
  * QVariant objects are converted to a string containing the JSON data.
  *
  *
  * Usage:
  *
  * \code
  * QVariantList people;
  *
  * QVariantMap bob;
  * bob.insert("Name", "Bob");
  * bob.insert("Phonenumber", 123);
  *
  * QVariantMap alice;
  * alice.insert("Name", "Alice");
  * alice.insert("Phonenumber", 321);
  *
  * people << bob << alice;
  *
  * QJson::Serializer serializer;
  * bool ok;
  * QByteArray json = serializer.serialize(people, &ok);
  *
  * if (ok) {
  *   qDebug() << json;
  * } else {
  *   qCritical() << "Something went wrong:" << serializer.errorMessage();
  * }
  * \endcode
  *
  * The output will be:
  *
  * \code
  *  "[ { "Name" : "Bob", "Phonenumber" : 123 },
  *     { "Name" : "Alice", "Phonenumber" : 321 } ]"
  * \endcode
  *
  * It's possible to tune the indentation level of the resulting string. \sa setIndentMode
  */
  class MUSIC_EXTRAS_EXPORT Serializer {
  public:
    Serializer();

     /**
      * This method generates a textual JSON representation and outputs it to the
      * passed in I/O Device.
      * @param variant The JSON document in its in-memory representation as generated by the
      * parser.
      * @param out Input output device
      * @param ok if a conversion error occurs, *ok is set to false; otherwise *ok is set to true
      */
    void serialize( const QVariant &variant, QIODevice* out, bool* ok);

    /**
      * This is a method provided for convenience. It turns the passed in in-memory
      * representation of the JSON document into a textual one, which is returned.
      * If the returned string is empty, the document was empty. If it was null, there
      * was a parsing error.
      *
      * @param variant The JSON document in its in-memory representation as generated by the
      * parser.
      *
      * \deprecated This method is going to be removed with the next major release of QJson.
      */
    QByteArray serialize( const QVariant &variant);

    /**
      * This is a method provided for convenience. It turns the passed in in-memory
      * representation of the JSON document into a textual one, which is returned.
      * If the returned string is empty, the document was empty. If it was null, there
      * was a parsing error.
      *
      * @param variant The JSON document in its in-memory representation as generated by the
      * parser.
      * @param ok if a conversion error occurs, *ok is set to false; otherwise *ok is set to true
      */
    QByteArray serialize( const QVariant &variant, bool *ok);

    /**
     * Allow or disallow writing of NaN and/or Infinity (as an extension to QJson)
     */
    void allowSpecialNumbers(bool allow);

    /**
     * Is Nan and/or Infinity allowed?
     */
    bool specialNumbersAllowed() const;

    /**
     * set output indentation mode as defined in QJson::IndentMode
     */
    void setIndentMode(IndentMode mode = QJson::IndentNone);


    /**
    * set double precision used while converting Double
    * \sa QByteArray::number
    */
    void setDoublePrecision(int precision);

    /**
     * Returns one of the indentation modes defined in QJson::IndentMode
     */
    IndentMode indentMode() const;

    /**
     * Returns the error message
     */
    QString errorMessage() const;

  private:
    class SerializerPrivate;
    TTK_DECLARE_PRIVATE(Serializer)

  };
}

#endif // QJSON_SERIALIZER_H
