
# Modern Filesystems

## Copy-on-Write

- Writes don't overwrite blocks.
  - Every block write reads the old block, updates it in cache,
    and then writes the data to a new location on disk.
  - This means the inode needs to be updated with a new block
    number for that block.
  - That's another block update, so we write the inode to a new
    block number.
  - That means we need to update the directory, etc.
- To make this more efficient, we structure the whole filesytem as
  one or more b-trees, maybe a data b-tree and a metadata b-tree.
  - We think of the filesystem as one big tree.
  - Any update results in a tree path to the root being updated,
    which produces a new tree root.
- That means that every change creates a new version of the root.
- So we can fix corruption by rolling back to the last version.
- Disks sometimes just mess up data, so we'd like to handle that
  too, so we give every block a checksum. We can recover the old
  version by rolling back in this case too.
- Performance:
  - We don't have 100% sequential writes like LFS, but
    we have mostly sequential writes and don't need GC.
- Features:
  - Snapshots: We can save / name old versions of the FS by pinning
    roots.
  - Reflink copies: We can copy a file just by making another reference
    to it, but treating the copy as a new file.

## Built in multi-disk support

- Some of these filesystems innately support a pool of disks.
- Once the filesystem knows about disks and can allocate data across
them, we can get the benefit of RAID in the FS.
- RAID0: We get for free.
- RAID1: Allocate two copies of each data block on different disks.
- RAID5/6: The filesystem does parity for data / metadata blocks, spread across
  differnet disks.

## The first modern FS: ZFS

- Released for Solaris by Sun Microsystems in like 1999.
- Solaris got released open source in like 2004 by Sun, including
ZFS.
- Solaris was released under an intentionally Linux-incompatible
open source license.
- Around the same time Oracle started working on a similar (clone)
filesystem for Linux called BTRFS.
- Then Oracle bought out Sun.

As of 2010:

- ZFS was the best CoW FS.
- It had working raid-z (raid5), raid-z2 (raid6)
- It ran on OpenSolaris and FreeBSD.
- BTRFS was almost usable, but raid5/6 was broken.

In 2026:

- ZFS was the best CoW FS.
- It had working raid-z (raid5), raid-z2 (raid6)
- It ran on OpenSolaris and FreeBSD.
- BTRFS was fully usable, if you babysit it, but raid5/6 was broken.
- Everyone wants to run Linux and ZFS, and whether the legal hacks
people are using work is quetionable.
- BTRFS breaks on disk full.
- ZFS never lets you remove disks.

## Other Operating Systems

Microsoft:

- NTFS on Desktop / Laptop
- Microsoft's CoW Filesystem on Server

Apple:

- Apple uses a CoW filesystem for both Mac and iPhone.
  - This has the reliability and checksum features.
  - It doesn't have multi-disk support.

FreeBSD:

- Using ZFS by default now.
- Great for a file server.

## Filesystems today on Linux

- Most distros give you ext4 by default.
- Fedora has moved to xfs, which is probably better.
- BTRFS is nice for features, but you've got to babysit it
and avoid full disks.
- ZFS is possible, but requires wacky module issues so don't
use it for your root partition. Check the license issue too
