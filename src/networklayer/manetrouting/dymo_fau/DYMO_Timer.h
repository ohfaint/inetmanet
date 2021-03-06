/*
 *  Copyright (C) 2006,2007 Christoph Sommer <christoph.sommer@informatik.uni-erlangen.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef DYMO_Timer_H
#define DYMO_Timer_H

#include <iostream>
#include <omnetpp.h>
#include "DYMO_Timeout_m.h"

//===========================================================================================
// simple, OMNeT++-aware timer class.
// Starting a DYMO_Timer will schedule a DYMO_Timeout cMessage to be sent to the parent when
// the timer exires. Warning: This cMessage is recycled for every iteration - do not delete!
//===========================================================================================
class DYMO_Timer : public cObject
{
	public:
		/**
		 * @param parent specifies the cSimpleModule that will receive a DYMO_Timeout message when this timer expires
		 * @param name helps differentiate DYMO_Timer instances
		 * @param interval sets the default interval after which to expire the DYMO_Timer
		 */
		DYMO_Timer(cSimpleModule* parent, std::string name, simtime_t interval = 0);

		~DYMO_Timer();

		/** @brief inherited from cObject */
		virtual const char* getFullName() const;

		/** @brief inherited from cObject */
		virtual std::string info() const;

		/** @brief inherited from cObject */
		virtual std::string detailedInfo() const;

		/** @brief returns whether the given timeout was started, but is not yet expired */
		bool isRunning();

		/** @brief returns whether the given timeout is to be considered expired */
		bool isExpired();

		/** @brief (re-)starts the timeout */
		void start(simtime_t interval = 0);

		/** @brief cancels the timeout */
		void cancel();

		/** @brief checks if the given cMessage is associated with this DYMO_Timer */
		bool owns(const cMessage* message) const;

		/** @brief returns the last set interval of this timer */
		simtime_t getInterval() const;

	protected:
		cSimpleModule* parent; /**< cSimpleModule that will receive cMessage instances that indicate timeouts */
		char* name; /**< descriptive name */
		simtime_t interval; /**< last set interval after which to expire this DYMO_Timer */
		DYMO_Timeout* message; /**< cMessage to be scheduled to remind simulation core of timeout */
		simtime_t expiresAt; /**< point in simulation time from where on this DYMO_Timer will be considered expired */
		bool active; /**< false if this DYMO_Timer is not currently active */

	public:
		friend std::ostream& operator<< (std::ostream& os, const DYMO_Timer& o);

};

std::ostream& operator<< (std::ostream& os, const DYMO_Timer& o);

#endif

