/*--------------------------------------------------------------------------
@COPYRIGHT  :
              Copyright 1996, Alex P. Zijdenbos, 
              McConnell Brain Imaging Centre,
              Montreal Neurological Institute, McGill University.
              Permission to use, copy, modify, and distribute this
              software and its documentation for any purpose and without
              fee is hereby granted, provided that the above copyright
              notice appear in all copies.  The author and McGill University
              make no representations about the suitability of this
              software for any purpose.  It is provided "as is" without
              express or implied warranty.
---------------------------------------------------------------------------- 
$RCSfile: MatrixSupport.h,v $
$Revision: 1.1.1.1 $
$Author: jason $
$Date: 2001-11-09 16:37:26 $
$State: Exp $
--------------------------------------------------------------------------*/
#ifndef _MATRIX_SUPPORT_H
#define _MATRIX_SUPPORT_H

#ifdef USE_COMPMAT
  #include <dcomplex.h>
#endif
#ifdef USE_FCOMPMAT
  #include <fcomplex.h>
#endif

typedef void (*FFTFUNC)(int n, double *real, double *imag);

//c functions declaration:
// double gauss(double mean, double std_dev);

/*
** Please only distribute this with it's associated FHT routine.
** This algorithm is apparently patented(!) and the code copyrighted. 
** See the comment with the fht routine for more info.
**   -Thanks,
**   Ron Mayer
*/

#ifdef GOOD_TRIG
#else
#define FAST_TRIG
#endif

#if defined(GOOD_TRIG)
#define FHT_SWAP(a,b,t) {(t)=(a);(a)=(b);(b)=(t);}
#define TRIG_VARS					         \
      int t_lam=0;
#define TRIG_INIT(k,c,s)					 \
     {								 \
      int i;							 \
      for (i=2 ; i<=k ; i++)					 \
          {coswrk[i]=costab[i];sinwrk[i]=sintab[i];}		 \
      t_lam = 0;					         \
      c = 1;							 \
      s = 0;							 \
     }
#define TRIG_NEXT(k,c,s)					 \
     {								 \
	 int i,j;	                                         \
         (t_lam)++;	  					 \
         for (i=0 ; !((1<<i)&t_lam) ; i++);			 \
         i = k-i;						 \
         s = sinwrk[i];						 \
         c = coswrk[i];						 \
         if (i>1)   						 \
            {	    						 \
             for (j=k-i+2 ; (1<<j)&t_lam ; j++);		 \
             j	       = k - j;					 \
             sinwrk[i] = halsec[i] * (sinwrk[i-1] + sinwrk[j]);  \
             coswrk[i] = halsec[i] * (coswrk[i-1] + coswrk[j]);  \
            }                                                    \
     }
#define TRIG_RESET(k,c,s)
#endif

#if defined(FAST_TRIG)
#define TRIG_VARS					 \
      double t_c,t_s;
#define TRIG_INIT(k,c,s)				 \
    {				        		 \
     t_c  = costab[k];				         \
     t_s  = sintab[k];				         \
     c    = 1;				    		 \
     s    = 0;				    		 \
    }
#define TRIG_NEXT(k,c,s)				 \
    {                                                    \
     double t = c;                                         \
     c   = t*t_c - s*t_s;				 \
     s   = t*t_s + s*t_c;				 \
    }
#define TRIG_RESET(k,c,s)
#endif

static double halsec[20]=
    {
     0,
     0,
     .54119610014619698439972320536638942006107206337801,
     .50979557910415916894193980398784391368261849190893,
     .50241928618815570551167011928012092247859337193963,
     .50060299823519630134550410676638239611758632599591,
     .50015063602065098821477101271097658495974913010340,
     .50003765191554772296778139077905492847503165398345,
     .50000941253588775676512870469186533538523133757983,
     .50000235310628608051401267171204408939326297376426,
     .50000058827484117879868526730916804925780637276181,
     .50000014706860214875463798283871198206179118093251,
     .50000003676714377807315864400643020315103490883972,
     .50000000919178552207366560348853455333939112569380,
     .50000000229794635411562887767906868558991922348920,
     .50000000057448658687873302235147272458812263401372
    };
static double costab[20]=
    {
     .00000000000000000000000000000000000000000000000000,
     .70710678118654752440084436210484903928483593768847,
     .92387953251128675612818318939678828682241662586364,
     .98078528040323044912618223613423903697393373089333,
     .99518472667219688624483695310947992157547486872985,
     .99879545620517239271477160475910069444320361470461,
     .99969881869620422011576564966617219685006108125772,
     .99992470183914454092164649119638322435060646880221,
     .99998117528260114265699043772856771617391725094433,
     .99999529380957617151158012570011989955298763362218,
     .99999882345170190992902571017152601904826792288976,
     .99999970586288221916022821773876567711626389934930,
     .99999992646571785114473148070738785694820115568892,
     .99999998161642929380834691540290971450507605124278,
     .99999999540410731289097193313960614895889430318945,
     .99999999885102682756267330779455410840053741619428
    };
static double sintab[20]=
    {
     1.0000000000000000000000000000000000000000000000000,
     .70710678118654752440084436210484903928483593768846,
     .38268343236508977172845998403039886676134456248561,
     .19509032201612826784828486847702224092769161775195,
     .09801714032956060199419556388864184586113667316749,
     .04906767432741801425495497694268265831474536302574,
     .02454122852291228803173452945928292506546611923944,
     .01227153828571992607940826195100321214037231959176,
     .00613588464915447535964023459037258091705788631738,
     .00306795676296597627014536549091984251894461021344,
     .00153398018628476561230369715026407907995486457522,
     .00076699031874270452693856835794857664314091945205,
     .00038349518757139558907246168118138126339502603495,
     .00019174759731070330743990956198900093346887403385,
     .00009587379909597734587051721097647635118706561284,
     .00004793689960306688454900399049465887274686668768
    };
static double coswrk[20]=
    {
     .00000000000000000000000000000000000000000000000000,
     .70710678118654752440084436210484903928483593768847,
     .92387953251128675612818318939678828682241662586364,
     .98078528040323044912618223613423903697393373089333,
     .99518472667219688624483695310947992157547486872985,
     .99879545620517239271477160475910069444320361470461,
     .99969881869620422011576564966617219685006108125772,
     .99992470183914454092164649119638322435060646880221,
     .99998117528260114265699043772856771617391725094433,
     .99999529380957617151158012570011989955298763362218,
     .99999882345170190992902571017152601904826792288976,
     .99999970586288221916022821773876567711626389934930,
     .99999992646571785114473148070738785694820115568892,
     .99999998161642929380834691540290971450507605124278,
     .99999999540410731289097193313960614895889430318945,
     .99999999885102682756267330779455410840053741619428
    };
static double sinwrk[20]=
    {
     1.0000000000000000000000000000000000000000000000000,
     .70710678118654752440084436210484903928483593768846,
     .38268343236508977172845998403039886676134456248561,
     .19509032201612826784828486847702224092769161775195,
     .09801714032956060199419556388864184586113667316749,
     .04906767432741801425495497694268265831474536302574,
     .02454122852291228803173452945928292506546611923944,
     .01227153828571992607940826195100321214037231959176,
     .00613588464915447535964023459037258091705788631738,
     .00306795676296597627014536549091984251894461021344,
     .00153398018628476561230369715026407907995486457522,
     .00076699031874270452693856835794857664314091945205,
     .00038349518757139558907246168118138126339502603495,
     .00019174759731070330743990956198900093346887403385,
     .00009587379909597734587051721097647635118706561284,
     .00004793689960306688454900399049465887274686668768
    };

void fft(int n, double *real, double *imag);
void ifft(int n, double *real, double *imag);

/*
** End of Ron Mayer's code
*/

void jacobi(double **, unsigned, double *, double **);
#ifdef USE_COMPMAT
void fft_basic(dcomplex *cbuffer,double *sintab, int buflog, int direct);
#endif
#ifdef USE_FCOMPMAT
void fft_basic_float(fcomplex *cbuffer,float *sintab, int buflog, int direct);
#endif

template <class Type> 
void allocateArray(unsigned n, Type *&array);
template <class Type>
void freeArray(Type *&array);

void inferDimensions(unsigned long nElements, unsigned& nrows, unsigned& ncols);
void inferDimensions(unsigned long nElements, unsigned& nslis, unsigned& nrows, 
		     unsigned& ncols);
#endif

