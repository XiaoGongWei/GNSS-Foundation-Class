//============================================================================
//
//  This file is part of GPSTk, the GPS Toolkit.
//
//  The GPSTk is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 3.0 of the License, or
//  any later version.
//
//  The GPSTk is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with GPSTk; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
//  
//  Copyright 2004, The University of Texas at Austin
//  Dagoberto Salazar - gAGE ( http://www.gage.es ). 2006, 2007, 2008
//
//============================================================================

//============================================================================
//
//This software developed by Applied Research Laboratories at the University of
//Texas at Austin, under contract to an agency or agencies within the U.S. 
//Department of Defense. The U.S. Government retains all rights to use,
//duplicate, distribute, disclose, or release this software. 
//
//Pursuant to DoD Directive 523024 
//
// DISTRIBUTION STATEMENT A: This software has been approved for public 
//                           release, distribution is unlimited.
//
//=============================================================================

/**
* @file SourceID.hpp
* gpstk::SourceID - Simple index to represent the source of data.
*/

#ifndef GFC_SENSORID_H
#define GFC_SENSORID_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <map>


/*

��GPSTK sourceID��ı��������GNSS_DATA_STRUCTURE��һ����
������Ҫ�޸ĳ����е�SensorType���Ǵ������ļ���ȡ�ģ�

*/


namespace gfc
{

	/** @addtogroup DataStructures */
	
	class SensorID
	{
	public:
		
		/// The type of source.���������
		enum SensorType
		{
			Unknown,
			GPS,        ///< GPS data
			Galileo,    ///< Galileo data
			Glonass,    ///< Glonass data
			Geosync,    ///< Geostationary data
			LEO,        ///< LEO data
			Transit,    ///< Transit data
			BDS,		///< Beidou System data
			Mixed,      ///< Mixed data
			UserDefined,///< UserDefined
			DGPS,       ///< Differential GPS data
			RTK,        ///< Real Time Kinematic data
			NSS,        ///< Navigation Satellites System 
			INS,        ///< Inertial System data
			Laser,      ///< ��������(SLR����)
			VLBI,       ///< VLBI����
			Last,       ///< used to extend this...
			Placeholder = Last+1000  //���ڽ�����չ;Last�Լ�Placeholder���ܸı�
		};


		/// empty constructor, creates an unknown source data object
		SensorID()
			: type(Unknown), sensorName("")
		{};


		/// Explicit constructor
		SensorID( SensorType st,
			std::string name )
			: type(st), sensorName(name)
		{};


		/// Copy constructor
		SensorID(const SensorID& s)
			: type(s.type), sensorName(s.sensorName)
		{};


		/// Equality operator requires all fields to be the same.
		virtual bool operator==(const SensorID& right) const;


		/// Ordering is arbitrary but required to be able to use a SourceID
		/// as an index to a std::map. If an application needs
		/// some other ordering, inherit and override this function.
		virtual bool operator<(const SensorID& right) const;


		/// Inequality operator
		bool operator!=(const SensorID& right) const
		{ return !(operator==(right)); }


		/// 'Greater than' operator
		bool operator>(const SensorID& right) const
		{  return (!operator<(right) && !operator==(right)); }


		/// 'Less or equal than' operator
		bool operator<=(const SensorID& right) const
		{ return (operator<(right) || operator==(right)); }


		/// 'Greater or equal than' operator
		bool operator>=(const SensorID& right) const
		{ return !(operator<(right)); }


		/// Assignment operator
		SensorID& operator=(const SensorID& right);


		/// Convenience output method
		virtual std::ostream& dump(std::ostream& s) const;


		/// Returns true if this is a valid SourceID. Basically just
		/// checks that none of the fields are undefined.
		virtual bool isValid() const;


		/// Destructor
		virtual ~SensorID() {};


		/// Method to create a new source type.
		static SensorType newSensorType(const std::string& s);


		// Fields

		/// Type of the data source (GPS receiver, Inertial system, etc)
		SensorType  type;
		
		
		/// Name of the data source
		std::string sensorName;
		
		
	private:


		static std::map< SensorType, std::string > stStrings;


	public:

#ifndef SWIG
		class Initializer
		{
		public:
			Initializer();
		};

		static Initializer SensorIDsingleton;
#endif

	}; // End of class 'SourceID'



	namespace StringUtils
	{
		/// Convert this object to a string representation
		std::string asString(const SensorID& p);		
	}



	/// Stream output for SourceID
	std::ostream& operator<<( std::ostream& s,
		const SensorID& p );



}  // End of namespace gpstk
#endif   // GPSTK_SOURCEID_HPP
