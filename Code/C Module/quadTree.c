//
// Created by João Portugal on 06/05/2020.
//


#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "quadTree.h"



int build_quadtree(const Stock *stocks, size_t stocks_size, QuadT tree)
  {
      QuadT fbg = NULL;
      QuadT fbd = NULL;
      QuadT fhg = NULL;
      QuadT fhd = NULL;
      double lat = 0.f, lon = 0.f;
      double res;
      assert(stocks != NULL);
      assert(tree != NULL);
      assert(tree->fbd == NULL);
      assert(tree->fbg == NULL);
      assert(tree->fhd == NULL);
      assert(tree->fhg == NULL);

      res = is_alone(tree, stocks, stocks_size, &lat, &lon);

      /* node is not alone */
      if(fabs(res - QUADTREE_NOT_ALONE) < DBL_EPSILON)
      {

          /* initialize tree size */
          tree->size = 1;

          /* create children */
          fbd = create_quadtree();

          fbd->coords.mLon = tree->coords.mLon;
          fbd->coords. mLat = tree->coords. mLat;


          if(build_quadtree(stocks, stocks_size, fbd) == 1)
          {
              tree->fbd = fbd;
              tree->size += tree->fbd->size;
              tree->value += tree->fbd->value;
          }
          else
          {
              --qstack_index;
              memset(fbd, 0, sizeof(*fbd));
          }

          fbg = create_quadtree();

          fbg->coords.mLat = tree->coords.mLat;
          fbg->coords.mLon = tree->coords.mLon;


          if(build_quadtree(stocks, stocks_size, fbg) == 1)
          {
              tree->fbg = fbg;
              tree->size += fbg->size;
              tree->value += fbg->value;
          }
          else
          {
              --qstack_index;
              memset(fbg, 0, sizeof(*fbg));
          }

          fhg = create_quadtree();

          fhg->coords.mLat = tree->coords.mLat;
          fhg->coords. mLon = tree->coords.mLon;

          if(build_quadtree(stocks, stocks_size, fhg) == 1)
          {
              tree->fhg = fhg;
              tree->size += fhg->size;
              tree->value += fhg->value;
          }
          else
          {

              --qstack_index;
              memset(fhg, 0, sizeof(*fhg));
          }

          fhd = create_quadtree();

          fhd->coords. mLat = tree->coords.mLat;
          fhd->coords. mLon = tree->coords.mLon;

          if(build_quadtree(stocks, stocks_size, fhd) == 1)
          {
              tree->fhd = fhd;
              tree->size += fhd->size;
              tree->value += fhd->value;
          }
          else
          {
              --qstack_index;
              memset(fhd, 0, sizeof(*fhd));
          }

          return 1;
      }

      /* node is alone */
      else if(fabs(res - QUADTREE_EMPTY) < DBL_EPSILON)
      {
          return 0;
      }
      else
      {
          tree->value = res;
          tree->size = 1;
          tree->coords.mLat = tree->coords. mLat = lat;
          tree->coords.mLon = tree->coords. mLon = lon;
          return 1;
      }
  }


  size_t find_lowest_element_in_qtree(const QuadT tree,
     const Stock * stocks, size_t stocks_size)
  {
      size_t b, e, i;
      b = 0, e = stocks_size - 1;
      while(e - b > 1)
      {
          i = (e + b) / 2;
          if(stocks[i].lat > tree->coords.mLat)
              e = (e + b - 1) / 2;
          else
              b = (e + b + 1) / 2;
          assert(b <= e);
      }
      return stocks[e].lat >= tree->coords.mLat ? b : e;
  }


  size_t find_highest_element_in_qtree(const QuadT tree,
     const Stock * stocks, size_t stocks_size)
  {
      size_t b, e, i;
      b = 0, e = stocks_size - 1;
      while(e - b > 1)
      {
          i = (e + b) / 2;
          if(stocks[i].lat > tree->coords. mLat)
              e = (e + b - 1) / 2;
          else
              b = (e + b + 1) / 2;
          assert(b <= e);
      }
      return stocks[b].lat <= tree->coords. mLat ? e : b;
  }

  double is_alone(const QuadT tree, const Stock * stocks,
     size_t stocks_size, double *lat, double *lon)
  {

      size_t count_valid;
      double res;
      size_t begin, end, i;
      assert(stocks_size > 0);
      assert(stocks != NULL);
      begin = find_lowest_element_in_qtree(tree, stocks, stocks_size);
      end = find_highest_element_in_qtree(tree, stocks, stocks_size);
      count_valid = 0;
      res = 0.f;
      for(i = begin + 1; i < end; i++)
      {
          if((stocks[i].lon > tree->coords.mLon
                || fabs(stocks[i].lon - tree->coords.mLon) < DBL_EPSILON)
             && (tree->coords. mLon > stocks[i].lon
                || fabs(stocks[i].lon - tree->coords. mLon) < DBL_EPSILON))
          {
              if(count_valid++ > 0)
                  return QUADTREE_NOT_ALONE;
              *lat = stocks[i].lat;
              *lon = stocks[i].lon;
              res = stocks[i].pot;
          }
      }
      return (count_valid == 0) ? QUADTREE_EMPTY : res;

  }

  QuadT create_quadtree()
  {
      if(qstack_index >= STACK_SIZE)
      {
          ++qstack_curr;
          if(qstack_curr >= STACK_HEIGHT)
          {
              fprintf(stderr,
                 "[qalloc::] overflow of quadtree stack size\n");
              exit(EXIT_FAILURE);
          }
          qstack_index = 0;
          qstack[qstack_curr] = (QuadT) calloc(STACK_SIZE, sizeof(**qstack));
          if(qstack[qstack_curr] == NULL)
          {
              perror("[qalloc::calloc] ");
              exit(EXIT_FAILURE);
          }
      }
  #ifndef NDEBUG
      {
          QuadT tree = qstack[qstack_curr] + (qstack_index);
          assert(tree != NULL);
          assert(tree->fbd == NULL);
          assert(tree->fbg == NULL);
          assert(tree->fhd == NULL);
          assert(tree->fhg == NULL);
      }
  #endif
      return qstack[qstack_curr] + (qstack_index++);
  }

  void free_quadtree()
  {
      while(qstack_curr >= 0)
      {
          free(qstack[qstack_curr--]);

      }
  }
