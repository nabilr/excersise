// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.



#include "net/quic/core/congestion_control/verus.h"


#include <algorithm>
#include <string>

#include "base/metrics/histogram_macros.h"
#include "net/quic/core/congestion_control/prr_sender.h"
#include "net/quic/core/congestion_control/rtt_stats.h"
#include "net/quic/core/crypto/crypto_protocol.h"
#include "net/quic/core/proto/cached_network_parameters.pb.h"
#include "net/quic/core/quic_bug_tracker.h"
#include "net/quic/core/quic_flags.h"

using std::max;
using std::min;


void SetCallbackHappened()
{
  DVLOG(1)<<"verus log " << "SetCallbackHappened";
}

namespace net {

namespace {
// Constants based on TCP defaults.
// The minimum cwnd based on RFC 3782 (TCP NewReno) for cwnd reductions on a
// fast retransmission.  The cwnd after a timeout is still 1.
//const QuicByteCount kMaxBurstBytes = 3 * kDefaultTCPMSS;
const float kRenoBeta = 0.7f;               // Reno backoff factor.
const uint32_t kDefaultNumConnections = 2;  // N-connection emulation.
//const float kRateBasedExtraCwnd = 1.5f;     // CWND for rate based sending.
}  // namespace

TcpVerusSenderBase::TcpVerusSenderBase(const QuicClock* clock,
                                       const RttStats* rtt_stats,
                                       bool reno,
                                       QuicConnectionStats* stats)
    : rtt_stats_(rtt_stats),
      stats_(stats),
      reno_(reno),
      num_connections_(kDefaultNumConnections),
      largest_sent_packet_number_(0),
      largest_acked_packet_number_(0),
      largest_sent_at_last_cutback_(0),
      min4_mode_(false),
      last_cutback_exited_slowstart_(false),
      slow_start_large_reduction_(false),
      rate_based_sending_(false),
      no_prr_(false) ,
      is_timer_expires(false),
      next_expiry_time_(clock_.Now() /*+ QuicTime::Delta::FromMilliseconds(1)*/)
      {
       
        timer_.Start(FROM_HERE, base::TimeDelta::FromMilliseconds(1), this,
                &net::TcpVerusSenderBase::SetCallbackHappened1);
               // base::Bind(&SetCallbackHappened));
        

      }

TcpVerusSenderBase::~TcpVerusSenderBase() {}

void TcpVerusSenderBase::SetCallbackHappened1() { 
  DVLOG(1)<<"verus timer called";
  
  next_expiry_time_ = clock_.Now() + QuicTime::Delta::FromMilliseconds(1);

}

QuicByteCount TcpVerusSenderBase::GetCongestionWindow() const {                                                                         
   return kDefaultTCPMSS;
   //return congestion_window_ * kDefaultTCPMSS;
}


QuicByteCount TcpVerusSenderBase::GetSlowStartThreshold() const {                                                                       
   return kDefaultTCPMSS;
   //return slowstart_threshold_ * kDefaultTCPMSS;
}

CongestionControlType TcpVerusSenderBase::GetCongestionControlType() const {                                                            
   return kCubic;
   //return reno_ ? kReno : kCubic;
}

void TcpVerusSenderBase::SetMinCongestionWindowInPackets(
       QuicPacketCount congestion_window) {
       
}





void TcpVerusSenderBase::SetFromConfig(const QuicConfig& config,
                                       Perspective perspective) {
}

void TcpVerusSenderBase::ResumeConnectionState(
    const CachedNetworkParameters& cached_network_params,
    bool max_bandwidth_resumption) {
  //QuicBandwidth bandwidth = QuicBandwidth::FromBytesPerSecond(
   //   max_bandwidth_resumption
    //      ? cached_network_params.max_bandwidth_estimate_bytes_per_second()
     //     : cached_network_params.bandwidth_estimate_bytes_per_second());
  //QuicTime::Delta rtt =
   //   QuicTime::Delta::FromMilliseconds(cached_network_params.min_rtt_ms());

  //SetCongestionWindowFromBandwidthAndRtt(bandwidth, rtt);
}

void TcpVerusSenderBase::SetNumEmulatedConnections(int num_connections) {
  num_connections_ = max(1, num_connections);
}

float TcpVerusSenderBase::RenoBeta() const {
  // kNConnectionBeta is the backoff factor after loss for our N-connection
  // emulation, which emulates the effective backoff of an ensemble of N
  // TCP-Reno connections on a single loss event. The effective multiplier is
  // computed as:
  return (num_connections_ - 1 + kRenoBeta) / num_connections_;
}

void TcpVerusSenderBase::OnCongestionEvent(
    bool rtt_updated,
    QuicByteCount bytes_in_flight,
    const CongestionVector& acked_packets,
    const CongestionVector& lost_packets) {
  if (rtt_updated && InSlowStart() &&
      hybrid_slow_start_.ShouldExitSlowStart(
          rtt_stats_->latest_rtt(), rtt_stats_->min_rtt(),
          GetCongestionWindow() / kDefaultTCPMSS)) {
    //ExitSlowstart();
  }
  for (CongestionVector::const_iterator it = lost_packets.begin();
       it != lost_packets.end(); ++it) {
    //OnPacketLost(it->first, it->second, bytes_in_flight);
  }
  for (CongestionVector::const_iterator it = acked_packets.begin();
       it != acked_packets.end(); ++it) {
    OnPacketAcked(it->first, it->second, bytes_in_flight);
  }
}

void TcpVerusSenderBase::OnPacketAcked(QuicPacketNumber acked_packet_number,
                                       QuicByteCount acked_bytes,
                                       QuicByteCount bytes_in_flight) {

    DVLOG(1) << " verus log";
}

bool TcpVerusSenderBase::OnPacketSent(
    QuicTime sent_time,
    QuicByteCount bytes_in_flight,
    QuicPacketNumber packet_number,
    QuicByteCount bytes,
    HasRetransmittableData is_retransmittable) {
									   DVLOG(1) << " verus log " <<   sent_time.get_time() << " " << bytes_in_flight << " " <<packet_number << " " << bytes;

  return true;
}

QuicTime::Delta TcpVerusSenderBase::TimeUntilSend(
    QuicTime now ,
    QuicByteCount bytes_in_flight) const {

    DVLOG(1) << " verus log TimeUntilSend ";

   if(now < next_expiry_time_ ) {
      DVLOG(1) << " verus log TimeUntilSend  within expiry time";
      return next_expiry_time_ - now;
   }
  return QuicTime::Delta::Zero();
}

void TcpVerusSenderBase::set_timer_expires(bool flag) {
  is_timer_expires = flag;
}

QuicBandwidth TcpVerusSenderBase::PacingRate(
    QuicByteCount bytes_in_flight) const {
  // We pace at twice the rate of the underlying sender's bandwidth estimate
  // during slow start and 1.25x during congestion avoidance to ensure pacing
  // doesn't prevent us from filling the window.
									   DVLOG(1) << " verus log";
  QuicTime::Delta srtt = rtt_stats_->smoothed_rtt();
  if (srtt.IsZero()) {
    srtt = QuicTime::Delta::FromMicroseconds(rtt_stats_->initial_rtt_us());
  }
  const QuicBandwidth bandwidth =
      QuicBandwidth::FromBytesAndTimeDelta(GetCongestionWindow(), srtt);
  if (rate_based_sending_ && bytes_in_flight > GetCongestionWindow()) {
    // Rate based sending allows sending more than CWND, but reduces the pacing
    // rate when the bytes in flight is more than the CWND to 75% of bandwidth.
    return 0.75 * bandwidth;
  }
  return bandwidth * (InSlowStart() ? 2 : (no_prr_ && InRecovery() ? 1 : 1.25));
}

QuicBandwidth TcpVerusSenderBase::BandwidthEstimate() const {
									   DVLOG(1) << " verus log";
  QuicTime::Delta srtt = rtt_stats_->smoothed_rtt();
  if (srtt.IsZero()) {
    // If we haven't measured an rtt, the bandwidth estimate is unknown.
    return QuicBandwidth::Zero();
  }
  return QuicBandwidth::FromBytesAndTimeDelta(GetCongestionWindow(), srtt);
}

bool TcpVerusSenderBase::InSlowStart() const {
									   DVLOG(1) << " verus log";
  return GetCongestionWindow() < GetSlowStartThreshold();
}

bool TcpVerusSenderBase::IsCwndLimited(QuicByteCount bytes_in_flight) const {
									   DVLOG(1) << " verus log";
    return true;
}

bool TcpVerusSenderBase::InRecovery() const {
									   DVLOG(1) << " verus log";
    return true;
}

void TcpVerusSenderBase::OnRetransmissionTimeout(bool packets_retransmitted) {
  //HandleRetransmissionTimeout();
									   DVLOG(1) << " verus log";
}

void TcpVerusSenderBase::OnConnectionMigration() {
									   DVLOG(1) << " verus log";
}

void TcpVerusSenderBase::SetCongestionWindowInPackets( 
QuicPacketCount congestion_window) {
									   DVLOG(1) << " verus log";
}

std::string TcpVerusSenderBase::GetDebugState() const {
									   DVLOG(1) << " verus log";
  return "";
}

void TcpVerusSenderBase::OnApplicationLimited(QuicByteCount bytes_in_flight) {}

}  // namespace net
