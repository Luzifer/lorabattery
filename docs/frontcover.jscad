function main () {
  return union(
    difference(
      // Base plate
      cube({size: [85, 35, 2]}),
      // Display
      cube({size: [26, 15, 2]}).translate([68-26, 28-15, 0]),
      // Button holes
      cylinder({r: 1, h: 2}).translate([26.5, 30, 0]),
      cylinder({r: 1, h: 2}).translate([26.5, 13.5, 0])
    ),

    // Board holders
    difference(
      cube({size: [3, 2, 9.3]}),
      cube({size: [1, 2, 7.3]})
    ).translate([74, 21, 2]),
    difference(
      cube({size: [3, 2, 9.3]}),
      cube({size: [1, 2, 7.3]}).translate([2, 0, 0])
    ).translate([21, 16, 2]),
    difference(
      cube({size: [2, 3, 9.3]}),
      cube({size: [2, 1, 7.3]}).translate([0, 2, 0])
    ).translate([61, 7.5, 2]),
    difference(
      cube({size: [2, 3, 9.3]}),
      cube({size: [2, 1, 7.3]}).translate([0, 2, 0])
    ).translate([31, 7.5, 2]),

    // Antenna holder
    difference(
      cylinder({r: 3.5, h: 20}),
      cylinder({r: 2.5, h: 20}).translate([1.7, 0, 0]),
      cube({size: [5, 50, 20]}).translate([-7, -5 ,0])
    ).rotateY(-90).translate([25, 5, 3])
  )
}

// vim: set ft=javascript :
