//
// Copyright (C) 2006 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

#ifndef MGMT80211SIMPLIFIEDSTA_H
#define MGMT80211SIMPLIFIEDSTA_H

#include <omnetpp.h>
#include "Ieee80211MgmtBase.h"
#include "NotificationBoard.h"


/**
 * Used in 802.11 infrastructure mode: handles management frames for
 * a station (STA). See corresponding NED file for a detailed description.
 * This implementation ignores many details.
 *
 * @author Andras Varga
 */
class INET_API Mgmt80211SimplifiedSTA : public Mgmt80211Base
{
  protected:
    // Associate Access Point
    struct AssociateAP
    {
        MACAddress address;
        int channel;
        int receiveSequence;
    };
    AssociateAP associateAP;

  protected:
    virtual int numInitStages() const {return 2;}
    virtual void initialize(int);

    virtual void handleMessage(cMessage *msg);

    /** Called by the NotificationBoard whenever a change occurs we're interested in */
    virtual void receiveChangeNotification(int category, cPolymorphic *details);

    /** @name Processing of different frame types */
    //@{
    virtual void handleDataFrame(W80211DataFrame *frame);
    virtual void handleAuthenticationFrame(W80211AuthenticationFrame *frame);
    virtual void handleDeauthenticationFrame(W80211DeauthenticationFrame *frame);
    virtual void handleAssociationRequestFrame(W80211AssociationRequestFrame *frame);
    virtual void handleAssociationResponseFrame(W80211AssociationResponseFrame *frame);
    virtual void handleReassociationRequestFrame(W80211ReassociationRequestFrame *frame);
    virtual void handleReassociationResponseFrame(W80211ReassociationResponseFrame *frame);
    virtual void handleDisassociationFrame(W80211DisassociationFrame *frame);
    virtual void handleBeaconFrame(W80211BeaconFrame *frame);
    virtual void handleProbeRequestFrame(W80211ProbeRequestFrame *frame);
    virtual void handleProbeResponseFrame(W80211ProbeResponseFrame *frame);
    //@}
};

#endif

