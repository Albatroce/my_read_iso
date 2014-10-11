/*
 **    This file is part of my_read_iso.
 **
 **    my_read_iso is free software;
 **    it under the terms of the GNU General Public License as published by
 **    the Free Software Foundation;
 **    (at your option) any later version.
 **
 **    my_read_iso is distributed in the hope that it will be useful,
 **    but WITHOUT ANY WARRANTY;
 **    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **    GNU General Public License for more details.
 **
 **    You should have received a copy of the GNU General Public License
 **    along with my_read_iso;
 **    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 **
 **    Copyright Alexandre Becoulet, 2003
 **    contact : alexandre.becoulet@epita.fr
 */

#ifndef ISO9660_H_
# define ISO9660_H_

# include <stdint.h>

struct endian32
{
  uint32_t le;
  uint32_t be;
} __attribute__ ((packed));

struct endian16
{
  uint16_t le;
  uint16_t be;
} __attribute__ ((packed));

# define ISO_BLOCK_SIZE 2048

#define ISO_DATE_LEN  7

enum iso_file_type
{
  iso_file_hidden   = 1,
  iso_file_isdir    = 2,
  iso_file_associat = 4,
  iso_file_useext   = 8,
  iso_file_useperm  = 16,
  iso_file_multidir = 128
};

struct iso_dir
{
  uint8_t    dir_size;
  uint8_t    ext_size;
  struct endian32  data_blk;
  struct endian32  file_size;
  char     date[ISO_DATE_LEN];
  uint8_t    type;

  uint8_t    unit_size;
  uint8_t    gap_size;

  struct endian16  vol_seq;
  uint8_t    idf_len;
} __attribute__ ((packed));

# define ISO_PRIM_VOLDESC_BLOCK 16

# define ISO_SYSIDF_LEN 32
# define ISO_VOLIDF_LEN 32
# define ISO_VOLSET_LEN 128
# define ISO_PUBIDF_LEN 128
# define ISO_DPREP_LEN  128
# define ISO_APP_LEN  128
# define ISO_CPRFIL_LEN 37
# define ISO_ABSFIL_LEN 37
# define ISO_BIBFIL_LEN 37
# define ISO_LDATE_LEN  17

struct iso_prim_voldesc
{
  uint8_t    vol_desc_type;
  char     std_identifier[5];
  uint8_t    vol_desc_version;
  uint8_t    unused1;
  char     syidf[ISO_SYSIDF_LEN];
  char     vol_idf[ISO_VOLIDF_LEN];
  uint8_t    unused2[8];
  struct endian32  vol_blk_count;
  uint8_t    unused4[32];
  struct endian16  vol_set_size;
  struct endian16  vol_seq_num;
  struct endian16  vol_blk_size;
  struct endian32  path_table_size;
  uint32_t   le_path_table_blk;
  uint32_t   le_opath_table_blk;
  uint32_t   be_path_table_blk;
  uint32_t   be_opath_table_blk;

  struct iso_dir   root_dir;
  uint8_t    unused5[34 - sizeof (struct iso_dir)];

  char     volset_idf[ISO_VOLSET_LEN];
  char     pub_idf[ISO_PUBIDF_LEN];
  char     dprep_idf[ISO_DPREP_LEN];
  char     app_idf[ISO_APP_LEN];

  char     copyright_file[ISO_CPRFIL_LEN];
  char     abstract_file[ISO_ABSFIL_LEN];
  char     bibli_file[ISO_BIBFIL_LEN];
  char     date_creat[ISO_LDATE_LEN];
  char     date_modif[ISO_LDATE_LEN];
  char     date_expir[ISO_LDATE_LEN];
  char     date_effect[ISO_LDATE_LEN];
  uint8_t    filestrutc_version;
} __attribute__ ((packed));

#endif /* !ISO9660_H_ */
