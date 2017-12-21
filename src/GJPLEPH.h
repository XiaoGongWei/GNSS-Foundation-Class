
//============================================================================
//
//  This file is part of GFC, the GNSS FOUNDATION CLASS.
//
//  The GFC is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 3.0 of the License, or
//  any later version.
//
//  The GFC is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with GFC; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
//
//  Copyright 2015, lizhen
//
//============================================================================

/****************************************************************************
*/

#ifndef  GFC_GJPLEPH_H
#define  GFC_GJPLEPH_H

#include <math.h>
#include <fstream>
#include <map>
#include "GString.h"
#include "GTime.h"

using namespace std;

namespace gfc
{

class GJPLEPH
{
    
public:
    
    struct INDICATOR
    {
        int start_pos;  //the tag of starting position
        int num_coeff;   // number of coefficients for every component
        int num_blocks;  // number of blocks of that planet
        INDICATOR()
        {
            start_pos = 0;
            num_coeff = 0;
            num_blocks = 0;
        }
    };
    
    struct JPLHEADER
    {
        int const_num ;
        std::map<GString,double> constant;
        int  KSIZE;
        int  NCOEFF;   //ÿ�����ݼ�¼���б�ѩ��ϵ���ĸ���(�������е�13������,9������+2��������+̫��ϵ����+����ϵ����)
        double start_jed;  //������ʼ��������
        double end_jed;    //����������������
        double record_span;  //������¼�ķ�Χ(��),DE405��32�����һ�Σ���ֵΪ32
        
       /*
         *
         * the order is like this, which is the same for the coefficients in the datafile
         * Mercury, Venus, Earth-Moon barycenter, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto,Moon and Sun, Nutation, Lunar libration
         *
         */
        std::vector<INDICATOR> ephindicator;
    };
    
    /*һ����¼������*/
    struct JPLRECORD
    {
        int index;
        int data_num;
        std::vector<double> record ;  //ÿ����¼�����ݶ��ļ���ʱ���ٶ�
        JPLRECORD()
        {
            index = 0;
            data_num = 0;
        }
        
    };
    
    /*�����е����嶨��*/
    enum BODYTYPE
    {
        UNKNOWNBODY = 0, MERCURY = 1, VENUS = 2,
        EARTH = 3,  //add by myself, because 3 only give out the earth-moon barycenter, NOT the earth barycenter
        MARS = 4, JUPITER = 5, 
        SATURN  = 6, URANUS= 7, NEPTUNE = 8, PLUTO =9, MOON = 10, SUN=11,
        SS_BARY = 12,
        EMBARY = 13, /* EARTH-MOON BARYCENTER*/
        NUTATIONS = 14, /* LONGITUDE and OBLIQ*/
        LIBRATIONS = 15  /* IF ON EPH FILE*/
    };
    
    /*
     THE NUMBERING CONVENTION FOR 'NTARG' AND 'NCENT' IS:
     C
     C                1 = MERCURY           8 = NEPTUNE
     C                2 = VENUS             9 = PLUTO
     C                3 = EARTH            10 = MOON
     C                4 = MARS             11 = SUN
     C                5 = JUPITER          12 = SOLAR-SYSTEM BARYCENTER
     C                6 = SATURN           13 = EARTH-MOON BARYCENTER
     C                7 = URANUS           14 = NUTATIONS (LONGITUDE AND OBLIQ)
     C                          15 = LIBRATIONS, IF ON EPH FILE
     C
     C             (IF NUTATIONS ARE WANTED, SET NTARG = 14. FOR LIBRATIONS,
     C              SET NTARG = 15. SET NCENT=0.)    
     */
    
    GJPLEPH();
   ~GJPLEPH();
   
   static void loadEphFile_a(GString filename);
    
   /* ephemeris test function */
   void EphTest(std::string testfilename);  			
    
   double GetConstant( GString const_name ) ;  //���ݳ������ƻ�ȡ������ֵ
   void SetUnit(bool km );
   void SetBARY(bool bary);
    
   void setEpoch( double et  );
   void setEpoch(GTime et );
   void getPos( int ncent, int ntarg, double* pv );
   void getPos_apparent( int ncent, int ntarg, double* pv);
    
private:
    
    static JPLHEADER  ephHeader;
    static std::vector<JPLRECORD> ephData;
    static double m_AU;       //���ĵ�λ����,��λΪkm
    static double m_EMRAT;   //����������
    static int ephversion;   //���������汾��"DE405","DE430"��
    
    // the position and velocity in solar system barycenter
    void calPos( int iplanet,int opt, double* pv);
    
    void interp(double coef[],double t[2],int ncf,int ncm,int na,int ifl,double posvel[6]);
    
    //void interp(double coef[],double t[2],int ncf,int ncm,int na,int ifl,double posvel[6]);
    void datasplit( double tt, double fr[2]);
    
    GTime m_epoch;  // the time system should be in TT
    long m_nr;  // the record number of the ephData for current epoch time
    double m_sun_SB[6];  // the position and velocity of sun in Solar System Barycentre
    double m_t[2];  //
    double m_aufac;  // tag for the unit transformation
    bool  m_bary; /* BARY   logical flag defining output center.only the 9 planets (entries 0-8) are affected.
                   BARY = TRUE =\ center is solar-system
                   barycenter = FALSE =\ center is sun
                   */
    bool m_km;  // tag for the ouput unit;
    
};

}  // end of namespace gfc

#endif   



