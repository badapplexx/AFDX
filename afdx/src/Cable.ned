//
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package afdx;

channel Cable extends ned.DatarateChannel
{
    @display("ls=blue");
    @labels(Cable);
    double length @unit(m) = default(0m);
    delay = replaceUnit(length / 2e8, "s"); //2e8m/s -> wave propogation speed
}

