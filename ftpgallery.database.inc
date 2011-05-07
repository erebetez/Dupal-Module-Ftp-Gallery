<?php

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

function ftpgallery_nodeapi(&$node, $op, $teaser, $page) {
  switch ($op) {
    case 'delete revision':
      // Notice that we're matching a single revision based on the node's vid.
      db_query('DELETE FROM {ftpgallery} WHERE vid = %d', $node->vid);
      break;
  }
}