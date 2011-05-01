<?php

// error handling
function _ftpgallery_formatError($node, $errorText, $warning = FALSE){
  if( !$node->error ){
    $node->error = array();
  }

  $output  = $warning ? t("Warning") : t("Error");
  $output .= ": ";
  $output .= check_plain($errorText);

  array_push( $node->error, $output );
  return $node;
}

function theme_ftpgallery_error($node) {
  $output = '<div class="ftpgallery_error">';

  foreach( $node->error as $errorText ){
    $output .= "<p>" . $errorText . "</p>";
  }

  $output .= _ftpgallery_debug($node);

  $output .= '</div>';
  return $output;
}

function _ftpgallery_debug($node){
  $output = "Debug info: <br />";

  $output .= $node->galleryurl . "<br />";

  if( count($node->gallery['thumbnails']) > 0 ){
    foreach($node->gallery['thumbnails'] as $thumbnail){
      $output .= $node->galleryurl . "/" . $thumbnail . "<br />";
    }
  }

  if( count($node->gallery['pictures']) > 0 ){
    foreach($node->gallery['pictures'] as $picture){
      $output .= $node->galleryurl . "/" . $picture . "<br />";
    }
  }
  return $output;
}