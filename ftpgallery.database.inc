<?php
/***********************************************************************************
* Drupal Module: FTP-Gallery
* Copyright (C) 2011 Etienne Rebetez, etienne.rebetez@oberwallis.ch
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*
***********************************************************************************/

// --- Database hooks ---

function ftpgallery_insert($node) {
  db_query("INSERT INTO {ftpgallery} (vid, nid, galleryurl, thumbid) VALUES (%d, %d, '%s', '%s')", $node->vid, $node->nid, $node->galleryurl, $node->thumbid);
}

function ftpgallery_update($node) {
  // if this is a new node or we're adding a new revision,
  if ($node->revision) {
    ftpgallery_insert($node);
  }
  else {
    db_query("UPDATE {ftpgallery} SET galleryurl = '%s', thumbid = '%s' WHERE vid = %d", $node->galleryurl, $node->thumbid, $node->vid);
  }
}

function ftpgallery_delete($node) {
  // Notice that we're matching all revision, by using the node's nid.
  db_query('DELETE FROM {ftpgallery} WHERE nid = %d', $node->nid);
}

function ftpgallery_load($node) {
  return db_fetch_object(db_query('SELECT galleryurl, thumbid FROM {ftpgallery} WHERE vid = %d', $node->vid));
}

// The node api is only used for database realated stuff at the moment.
function ftpgallery_nodeapi(&$node, $op, $teaser, $page) {
  switch ($op) {
    case 'delete revision':
      // Notice that we're matching a single revision based on the node's vid.
      db_query('DELETE FROM {ftpgallery} WHERE vid = %d', $node->vid);
      break;
  }
}