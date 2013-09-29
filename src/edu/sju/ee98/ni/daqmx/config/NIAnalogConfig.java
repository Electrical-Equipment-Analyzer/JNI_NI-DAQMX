/*
 * Copyright (c) 2013, St. John's University and/or its affiliates. All rights reserved.
 * Department of Electrical Engineering.
 */
package edu.sju.ee98.ni.daqmx.config;

/**
 *
 * @author 102m05008
 */
public interface NIAnalogConfig {

    public String getPhysicalChannel();

    public double getMinVoltage();

    public double getMaxVoltage();

    public double getRate();

    public long getLength();
}
