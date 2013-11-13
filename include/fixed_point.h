/*    This file is part of fixed_point
      The aim of this software is to provide some support of fixed
      point computation
      Copyright (C) 2013  Julien Thevenon ( julien_thevenon at yahoo.fr )

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#include <stdint.h>
#include <iostream>
#include <string>
#include "math.h"
#include <inttypes.h>

#ifndef FIXED_POINT_H
#define FIXED_POINT_H

#ifdef COMPUTE_32
double to_double(uint32_t p_value,uint8_t nb_digit_after)
{
  double l_result = 0;
  for(uint32_t i = 0 ; i < 8*sizeof(uint32_t) ; i++)
    {
      uint32_t l_mod = p_value % 2;
      p_value = p_value / 2;
      //             std::cout << "i = " << i << " 2^ " << i << "=" << pow(2,i) << " mod = " << l_mod << std::endl ;
      int32_t j = i - nb_digit_after ; 
      //          std::cout << "Fixed => j = " << j << " 2^ " << j << "=" << pow(2,j) << " mod = " << l_mod << std::endl ;
      double l_add = pow(2,j);
      //       std::cout << "Add = " << l_add << std::endl ;
      if(i != 8*sizeof(uint32_t) - 1)
	{
	  l_result += l_mod * l_add;
	}
      else
	{
	  l_result -= l_mod * l_add;
	}
      //       std::cout << "internediary result = " << l_result << std::endl ;
    }
  return l_result;

}

uint32_t fixed_mult(uint32_t p_value1,uint32_t p_value2,uint8_t p_nb_digit_after)
{
  //  std::cout << "number1 = 0x" << std::hex << p_value1 << std::dec << std::endl ;
  //  std::cout << "number2 = 0x" << std::hex << p_value2 << std::dec << std::endl ;
  uint32_t l_produit = (p_value1 * p_value2);
  //  std::cout << "produit = 0x" << std::hex << l_produit << std::dec << std::endl ;
  if(l_produit & 0x80000000)
    {
      l_produit = (l_produit >> p_nb_digit_after) + (((1 << p_nb_digit_after) -1) << (8*sizeof(uint32_t)-p_nb_digit_after));
    }
  else
    {
      l_produit = l_produit >>  p_nb_digit_after;
    }
  return l_produit;
}
 
void display(std::string p_name,uint32_t p_value,uint8_t nb_digit_after)
{
  std::cout << p_name << "\t" << std::hex << p_value << std::dec << "\t" << to_double(p_value,nb_digit_after) << std::endl ;
}

#endif
double to_double16(uint16_t p_value,uint8_t nb_digit_after)
{
  //  std::cout << "DISPLAYDISPLAYDISPLAYDISPLAYDISPLAY" << std::endl ;
  double l_result = 0;
  for(uint16_t i = 0 ; i < 8*sizeof(uint16_t) ; i++)
    {
      uint16_t l_mod = p_value % 2;
      p_value = p_value / 2;
      //         std::cout << "i = " << i << " 2^ " << i << "=" << pow(2,i) << " mod = " << l_mod << std::endl ;
      int32_t j = i - nb_digit_after ; 
      //          std::cout << "Fixed => j = " << j << " 2^ " << j << "=" << pow(2,j) << " mod = " << l_mod << std::endl ;
      double l_add = pow(2,j);
      //       std::cout << "Add = " << l_add << std::endl ;
      if(i != 8*sizeof(uint16_t) - 1)
	{
	  l_result += l_mod * l_add;
	}
      else
	{
	  l_result -= l_mod * l_add;
	}
      //       std::cout << "internediary result = " << l_result << std::endl ;
    }
  return l_result;

}
uint16_t minus16(uint16_t p_value)
{
  return (~p_value)+1;
}
uint16_t abs16(uint16_t p_value)
{
  return ((0x8000 & p_value) ? minus16(p_value): p_value);
}

void display16(std::string p_name,uint16_t p_value,uint8_t nb_digit_after)
{
  std::cout << p_name << "\t0x" << std::hex << p_value << std::dec << "\t" << to_double16(p_value,nb_digit_after) << std::endl ;
}

uint16_t fixed_mult16(uint16_t p_value1,uint16_t p_value2,uint8_t p_nb_digit_after)
{
    bool l_neg = (0x8000 & p_value1) ^ (0x8000 & p_value2);
    uint16_t l_abs1 = abs16(p_value1);
    uint16_t l_abs2 = abs16(p_value2);
    uint32_t l_produit = l_abs1 * l_abs2;
    l_produit = l_produit >> p_nb_digit_after;
    if(l_neg) 
      {
	l_produit = minus16(l_produit);
      }

  return l_produit;
}
 
#endif // FIXED_POINT_H
//EOF
