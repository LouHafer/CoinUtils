/* $Id$ */
/*
  Copyright (C) 2002, 2003 International Business Machines Corporation
  and others.  All Rights Reserved.

  This code is licensed under the terms of the Eclipse Public License (EPL).
*/
#ifndef CoinCDefine_H
#define CoinCDefine_H

/** This has #defines etc for the "C" interface to Coin.
    If COIN_EXTERN_C defined then an extra extern C
*/

#if defined(CLP_EXTERN_C)
#define COIN_EXTERN_C
#define COIN_NO_SBB
#define COIN_NO_CBC
#endif
#if defined(SBB_EXTERN_C)
#define COIN_EXTERN_C
#define COIN_NO_CLP
#endif
#if defined(CBC_EXTERN_C)
#define COIN_EXTERN_C
#define COIN_NO_CLP
#endif
/* We need to allow for Microsoft */
#ifndef COINLIBAPI

#if defined(CBCCINTERFACEDLL_EXPORTS) || defined(CLPMSDLL)
#if defined(COIN_EXTERN_C)
#define COINLIBAPI __declspec(dllexport)
#else
#define COINLIBAPI __declspec(dllexport)
#endif
#define COINLINKAGE __stdcall
#define COINLINKAGE_CB __cdecl
#else
#if defined(COIN_EXTERN_C)
#define COINLIBAPI extern "C"
#else
#define COINLIBAPI
#endif
#define COINLINKAGE
#define COINLINKAGE_CB
#endif

#endif
/** User does not need to see structure of model but C++ code does */
#if defined(CLP_EXTERN_C)
/* Real typedef for structure */
class CMessageHandler;
typedef struct {
  ClpSimplex *model_;
  CMessageHandler *handler_;
} Clp_Simplex;
#else
typedef void Clp_Simplex;
#endif

#ifndef COIN_NO_SBB
typedef int (COINLINKAGE_CB *cbc_incumbent_callback)(void *cbcModel, double obj, int nz, char **vnames, double *x, void *appData);

/** typedef for cbc callback to monitor the progress of the search
 * in terms of improved upper and lower bounds */
typedef int(COINLINKAGE_CB *cbc_progress_callback)(void *model,
                                                   int phase,
                                                   int step,
                                                   const char *phaseName,
                                                   double seconds,
                                                   double lb,
                                                   double ub,
                                                   int nint,
                                                   int *vecint,
                                                   void *cbData
                                                   );

#endif


#ifdef CBC_THREAD
#include <pthread.h>
#endif

#ifndef COIN_NO_CLP
/** typedef for user call back.
 The cvec are constructed so don't need to be const*/
#if COIN_BIG_INDEX == 0
typedef void(COINLINKAGE_CB *clp_callback)(Clp_Simplex *model, int msgno, int ndouble,
  const double *dvec, int nint, const int *ivec,
  int nchar, char **cvec);
#elif COIN_BIG_INDEX == 1
typedef void(COINLINKAGE_CB *clp_callback)(Clp_Simplex *model, int msgno, int ndouble,
  const double *dvec, int nint, const long *ivec,
  int nchar, char **cvec);
#else
typedef void(COINLINKAGE_CB *clp_callback)(Clp_Simplex *model, int msgno, int ndouble,
  const double *dvec, int nint, const long long *ivec,
  int nchar, char **cvec);
#endif
#endif
/** User does not need to see structure of model but C++ code does */
#if defined(SBB_EXTERN_C)
/* Real typedef for structure */
class Sbb_MessageHandler;
typedef struct {
  OsiClpSolverInterface *solver_;
  SbbModel *model_;
  Sbb_MessageHandler *handler_;
  char *information_;
} Sbb_Model;
#else
typedef void Sbb_Model;
#endif
#if defined(CBC_EXTERN_C)
/* Real typedef for structure */
class Cbc_MessageHandler;
typedef struct {
  OsiClpSolverInterface *solver_;
  CbcModel *model_;
  CbcSolverUsefulData *cbcData;
  Cbc_MessageHandler *handler_;
  std::vector< std::string > cmdargs_;
  char relax_;

  // buffer for columns
  int colSpace;
  int nCols;
  int cNameSpace;
  int *cNameStart;
  char *cInt;
  char *cNames;
  double *cLB;
  double *cUB;
  double *cObj;

  // buffer for rows
  int rowSpace;
  int nRows;
  int rNameSpace;
  int *rNameStart;
  char *rNames;
  double *rLB;
  double *rUB;
  int rElementsSpace;
  int *rStart;
  int *rIdx;
  double *rCoef;

  // for fast search of columns
  void *colNameIndex;
  void *rowNameIndex;

  cbc_incumbent_callback inc_callback;
  cbc_progress_callback progr_callback;
  void *icAppData;
  void *pgrAppData;

#ifdef CBC_THREAD
  pthread_mutex_t cbcMutex;
#endif
} Cbc_Model;
#else
typedef void Cbc_Model;
#endif
#ifndef COIN_NO_SBB
/** typedef for user call back.
 The cvec are constructed so don't need to be const*/
typedef void(COINLINKAGE_CB *sbb_callback)(Sbb_Model *model, int msgno, int ndouble,
  const double *dvec, int nint, const int *ivec,
  int nchar, char **cvec);

typedef void(COINLINKAGE_CB *cbc_callback)(Cbc_Model *model, int msgno, int ndouble,
  const double *dvec, int nint, const int *ivec,
  int nchar, char **cvec);


/** typedef for cbc cut callback osiSolver needs to be an OsiSolverInterface object,
 * osiCuts is an OsiCuts object and appdata is a pointer that will be passed to the cut
 * generation, you can use it to point to a data structure with information about the original problem,
 * for instance
 **/
typedef void(COINLINKAGE_CB *cbc_cut_callback)(void *osiSolver, void *osiCuts, void *appdata);
#endif
#if COIN_BIG_INDEX == 0
typedef int CoinBigIndex;
#elif COIN_BIG_INDEX == 1
typedef long CoinBigIndex;
#else
typedef long long CoinBigIndex;
#endif
/* just in case used somewhere */
#undef COIN_NO_CLP
#undef COIN_NO_SBB
#undef COIN_NO_CBC
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
