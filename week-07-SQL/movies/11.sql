-- query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated

-- using LIMIT here.

SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC LIMIT 5;
