# Use an official Python runtime as a parent image
FROM python:2.7-slim

# Set the working directory to /hello
WORKDIR /hello

# Copy the current directory contents into the container at /hello
ADD . /hello

# Run main.py when the container launches
CMD ["python", "main.py"]
