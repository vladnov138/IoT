from datetime import datetime

from pydantic import BaseModel, Field


class TemperatureValue(BaseModel):
    value: float
    location: str
    device_id: str
    timestamp: datetime = Field(default_factory=datetime.now)
