FROM python:3.12-slim

# Install build tools
RUN apt-get update && \
    apt-get install -y build-essential cmake && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

# 1) Build both binaries
COPY cpp_tools/ ./cpp_tools/
WORKDIR /app/cpp_tools
RUN make

# 5) Copy backend code
WORKDIR /app/backend
COPY backend/ ./

# 6) Install Pipenv and Python deps
RUN pip install --no-cache-dir pipenv && \
    pipenv install --deploy --ignore-pipfile


# Collect static files
RUN pipenv run python manage.py collectstatic --noinput


# 7) Expose port
EXPOSE 8000

# 8) Start the Django app with Gunicorn
ENV PATH="/app/backend/.venv/bin:$PATH"
CMD ["pipenv", "run","gunicorn", "rtl2cfg.wsgi:application", "--bind", "0.0.0.0:8000", "--access-logfile", "-", "--error-logfile", "-"]

