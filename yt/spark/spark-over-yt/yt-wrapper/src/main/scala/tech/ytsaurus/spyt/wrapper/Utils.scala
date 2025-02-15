package tech.ytsaurus.spyt.wrapper

import java.net.InetAddress
import scala.concurrent.duration._

object Utils {
  def parseDuration(s: String): Duration = {
    val regex = """(\d+)(.*)""".r
    s match {
      case regex(amount, "") => amount.toInt.seconds
      case regex(amount, "s") => amount.toInt.seconds
      case regex(amount, "m") => amount.toInt.minutes
      case regex(amount, "min") => amount.toInt.minutes
      case regex(amount, "h") => amount.toInt.hours
      case regex(amount, "d") => amount.toInt.days
      case regex(_, unit) => throw new IllegalArgumentException(s"Unknown time unit: $unit")
      case _ => throw new IllegalArgumentException(s"Illegal time format: $s")
    }
  }

  def flatten[A, B](seq: Seq[Either[A, B]]): Either[A, Seq[B]] = {
    seq
      .find(_.isLeft)
      .map(e => Left(e.left.get))
      .getOrElse(Right(seq.map(_.right.get)))
  }

  def ytNetworkProjectEnabled: Boolean = sys.env.contains("YT_NETWORK_PROJECT_ID")

  def ytHostIp: String = sys.env("YT_IP_ADDRESS_DEFAULT")

  def ytHostnameOrIpAddress: String = {
    if (ytNetworkProjectEnabled) ytHostIp else InetAddress.getLocalHost.getHostName
  }
}
