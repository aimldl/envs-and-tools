* Draft: 2021-01-18 (Mon)
# Setting the library types
Check that your media collection has been named and organized in a way that Plex will understand. If not, you may notice content isn’t recognized, is mis-matched, or not found at all.

## Library types
Libraries currently have one of five types:
 
1. Movies — Feature movies like “Gone with the Wind (1939)”
2. TV Shows — “Dexter”, “Days of our Lives”, etc.
3. Music — Your music collection
4. Photos — Images from your hard drive or applications like Aperture and iPhoto.
5. Other Videos — Videos you’ve made at home or noncommercial material that has never been broadcast (e.g., media not appearing in online databases). You can also use this type for obscure content or arbitrary video files, clips, etc. Items in Home Videos Libraries will not download artwork or other metadata from internet sources.

Source: [Support](https://support.plex.tv/) > [Articles](https://support.plex.tv/articles/) > [Overview](https://support.plex.tv/articles/200288916-overview/)

## Media file name convention
- Movies are gathered together in a “Movies” type folder, TV Shows in a “TV Shows” type folder, etc.
- Movies are named as follows:
  ```text
  [Movie_Name (Release_Year)]
  e.g., Avatar (2009).mp4
  ```
* TV Show episodes are named with the season and episode:
```
[Show Name SxxEyy]
e.g., Dexter s01e01.mp4
```
* TV Show episodes are stored in their own folder as follows:
```
/TV Shows/Show Name/Season/episodes
e.g., /TV Shows/Dexter/Season 01/Dexter s01e01.mp4
      /TV Shows/Rick and Morty/Season 04/Rick and Morty s04e01.mkv
```
Source: [Support](https://support.plex.tv/) > [Articles](https://support.plex.tv/articles/) > [Installation](https://support.plex.tv/articles/200288586-installation/)

## Music folders

> ```text
> /Media
>    /Movies
>       movie content
>    /Music
>       music content
>    /TV Shows
>       television content
> ```

- `Music/ArtistName/AlbumName/TrackNumber - TrackName.ext`

> ```text
> /Music
>    /Pink Floyd
>       /Wish You Were Here
>          01 - Shine On You Crazy Diamond (Parts I-V).m4a
>          02 - Welcome to the Machine.mp3
>          03 - Have a Cigar.mp3
>    /Foo Fighters
>       /One By One
>       /There is Nothing Left to Lose
>    /U2
>       /Joshua Tree
> ```

Various artists

> ```text
> /Music
>    /Various Artists
>       /Guardians Of The Galaxy - Awesome Mix Vol. 1
>          01 - Hooked On A Feeling.mp3
>          02 - Go All The Way.mp3
>          03 - Spirit In The Sky.mp3
>       /The Crow - Original Motion Picture Soundtrack
>          01 - Burn.mp3
>          02 - Golgotha Tenement Blues.mp3
>          03 - Big Empty.mp3
> ```

Source: [Support](https://support.plex.tv/) > [Articles](https://support.plex.tv/articles/) > [Adding Music Media From Folders](https://support.plex.tv/articles/200265296-adding-music-media-from-folders/)

Multi-disc
``` text
Music /
   Artist /
      Albumartist - Albumtitle /
         1. trackartist - tracktitle.mp3
         2. trackartist - tracktitle.mp3
         ...
```

a multi-disc album

``` text
Music /
   Artist /
      Albumartist - Albumtitle /
         Disc 1 /
            1. trackartist - tracktitle.mp3
            2. trackartist - tracktitle.mp3
            ...
         Disc 2 /
            1. trackartist - tracktitle.mp3
            2. trackartist - tracktitle.mp3
            ...
```
source: [Organizing Music - Soundtracks and Various Artists (Hit collections)](https://forums.plex.tv/t/organizing-music-soundtracks-and-various-artists-hit-collections/121354)

TODO:
Source: [Support](https://support.plex.tv/) > [Articles](https://support.plex.tv/articles/) > [Your Media](https://support.plex.tv/articles/categories/your-media/) >  [Music Files (Naming and Organizing)}(https://support.plex.tv/articles/categories/your-media/naming-and-organizing-music-media/)
