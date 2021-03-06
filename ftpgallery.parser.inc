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

/**
 * Function to parse the pictures and thumbnails in the folder.
 * Looks for thumbnails in a subfolder or with the prefix.
 */
function _ftpgallery_parseGalleryFolder($node) {
  $thumbnails = array();
  $pictures = array();

  // get files in the gallery folder
  $fileNameList = scandir( _ftpgallery_galleryPath($node) );

  $isThumbnailFolder = _ftpgallery_isThumbnailPrefixAFolder($node, $fileNameList);

  // remove thumbnails or folders from the List that matches the thumbnail prefix
  $fileNameList = preg_grep("/^" . $node->thumbid ."/", $fileNameList, PREG_GREP_INVERT);

  foreach($fileNameList as $fileName) {
    if( !_ftpgallery_isValidFileType($fileName) ) {
      continue;
    }

    $thumbnail = _ftpgallery_getThumbnailName($fileName, $node->thumbid, $isThumbnailFolder);

    if( _ftpgallery_galleryPathExists( $node, $thumbnail ) ){
      array_push($pictures, $fileName);
      array_push($thumbnails, $thumbnail);
      continue;
    }
    drupal_set_message(t("No matching thumbnail for picture %file. Thumbnail name %thumb ",
                         array('%file' => check_plain($fileName), '%thumb' => check_plain($thumbnail))),
                         'warning');
  }

  $node->gallery = array();
  $node->gallery['thumbnails'] = $thumbnails;
  $node->gallery['pictures'] = $pictures;
  return $node;
}

/// This function checks if the thumbnail prefix is in fact a subfolder.
function _ftpgallery_isThumbnailPrefixAFolder($node, $fileNameList){
   $thumbnailPrefix = "/^" . $node->thumbid . "$/";
   return (count(preg_grep($thumbnailPrefix, $fileNameList)) > 0);
}

function _ftpgallery_isValidFileType($fileName){
  $allowedFileTypes = variable_get('ftpgallery_allowedfiletypes', 'jpg jpeg png');
  $allowedFileTypes = explode(" ", $allowedFileTypes);

  $fileNameEnding = strtolower(end(explode(".", $fileName)));

  foreach($allowedFileTypes as $ending){
    if( $fileNameEnding == $ending ) {
      return true;
    }
  }

  return false;
}

function _ftpgallery_getThumbnailName($fileName, $thumbnailPrefix, $isFolder = FALSE){
  if( $isFolder ){
    return $thumbnailPrefix . "/" . $fileName;
  }

  return $thumbnailPrefix . $fileName;
}


/// Reads the content of a folder and returns an array with only the folders.
function _ftpgallery_readFolders($scanPath){
  $folderList = array();

  if( !file_exists($scanPath) ){
    return $folderList;
  }

  $fileNameList = scandir( $scanPath );
  foreach( $fileNameList as $file ){
    if( !is_dir($file) ){
      array_push($folderList, $file);
    }
  }
  return $folderList;
}