//Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2018.2 (lin64) Build 2258646 Thu Jun 14 20:02:38 MDT 2018
//Date        : Sat Nov 17 10:14:10 2018
//Host        : gentoo running 64-bit Gentoo Base System release 2.6
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (led_8bits_tri_o);
  output [7:0]led_8bits_tri_o;

  wire [7:0]led_8bits_tri_o;

  design_1 design_1_i
       (.led_8bits_tri_o(led_8bits_tri_o));
endmodule
