<?php

function _ftpgallery_parseGalleryFolder($node) {
  $thumbnails = array();
  $pictures = array();

  $fileNameList = _ftpgallery_getPictureNameList($node);

  $isThumbnailFolder = _ftpgallery_isThumbnailPrefixAFolder($node, $fileNameList);

  foreach($fileNameList as $fileName) {
    if( !_ftpgallery_isValidFileType($fileName) ) {
      continue;
    }

    $thumbnail = _ftpgallery_getThumbnail($fileName, $node->thumbid, $isThumbnailFolder);

    if( _ftpgallery_galleryPathExists( $node, $thumbnail ) ){
      array_push($pictures, $fileName);
      array_push($thumbnails, $thumbnail);
      continue;
    }
    drupal_set_message(t("No matching thumbnail for picture %file. Thumbnailname %thumb ",
                         array('%file' => check_plain($fileName)),
                         array('%thumb' => check_plain($thumbnail)),
                         'warning' ));
  }

  $node->gallery = array();
  $node->gallery['thumbnails'] = $thumbnails;
  $node->gallery['pictures'] = $pictures;
  return $node;
}

function _ftpgallery_getPictureNameList($node){
  // get files in the gallery folder
  $fileNameList = scandir( _ftpgallery_galleryPath($node) );

  // remove thumbnails or folders from the List that matches the thumbnail prefix
  $fileNameList = preg_grep("/^" . $node->thumbid ."/", $fileNameList, PREG_GREP_INVERT);

  return $fileNameList;
}

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

//   drupal_set_message(t("%file is no valid filetype. Check the settings. ",
//                        array('%file' => check_plain($fileName)), 'warning' ));

  return false;
}

function _ftpgallery_getThumbnail($fileName, $thumbnailPrefix, $isFolder = FALSE){
  if( $isFolder ){
    return $thumbnailPrefix . "/" . $fileName;
  }

  return $thumbnailPrefix . $fileName;
}